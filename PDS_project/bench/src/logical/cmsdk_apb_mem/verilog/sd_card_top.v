//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
//                                                                              //
//  Author: meisq                                                               //
//          msq@qq.com                                                          //
//          ALINX(shanghai) Technology Co.,Ltd                                  //
//          heijin                                                              //
//     WEB: http://www.alinx.cn/                                                //
//     BBS: http://www.heijin.org/                                              //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// Copyright (c) 2017,ALINX(shanghai) Technology Co.,Ltd                        //
//                    All rights reserved                                       //
//                                                                              //
// This source file may be used and distributed without restriction provided    //
// that this copyright statement is not removed from the file and that any      //
// derivative work contains the original copyright notice and the associated    //
// disclaimer.                                                                  //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

//==========================================================================
//  Revision History:
//  Date          By            Revision    Change Description
//--------------------------------------------------------------------------
//  2017/6/21    meisq         1.0         Original
//*************************************************************************/
module sd_card_top
(
	input            HCLK,
    input            cs,
	input            rst,
    input            wr_en,
    input[31:0]      wr_data,                    // input  [31:0]
    input[21:0]      waddr,						//waddr = addr[23:2];
    input[21:0]      rd_addr,					//raddr  = HADDR[23:2];[1,0]
    input            rd_en,

	//	SPI interface 
	output           SD_nCS,                    //SD card chip select (SPI mode)
	output           SD_DCLK,                   //SD card clock
	output           SD_MOSI,                   //SD card controller data output
	input            SD_MISO,                   //SD card controller data input
	
	// AHB feedback signals
	output[31:0]     rd_data
	);

	wire[2:0]		spi_state;
	reg                 	nCS_ctrl;                  //SPI module chip select control
	reg                 	spi_wr_req;                //SPI module data sending request
	wire                 spi_wr_ack;                //SPI module data request response
	reg[7:0]            spi_data_in;               //SPI module send data
	wire[7:0]            spi_data_out;              //SPI module data returned


	reg[31:0]           clk_div;					// 0 
	reg[31:0]			spi_write_data;				// 1
	reg[31:0]			spi_read_data;				// 2
	reg[31:0]			start_stop;					// 3
	reg[31:0]			cs_control;					// 4


// assign SPI_LOW_SPEED_DIV = 16'd498;			 // spi clk speed = clk speed /((SPI_LOW_SPEED_DIV + 2) * 2 )
// assign SPI_HIGH_SPEED_DIV = 16'd2;			 // spi clk speed = clk speed /((SPI_LOW_SPEED_DIV + 2) * 2 )


always @(posedge HCLK or negedge rst) begin
	if(~rst)begin
	end
	else begin
		
	end
end

reg[31:0] temp_rd_data;
assign rd_data = temp_rd_data;//(rd_addr[2:0]==3'b000)?INITIALISED:(rd_addr[2:0]==3'b010)?32'hff:32'h1313;


//		for read
always @(posedge HCLK or negedge rst) begin
	if(~rst)
		begin
			temp_rd_data <= 32'd0;
		end
	else
		begin
			if(cs && rd_en)	begin
				case (rd_addr)
					0:begin
						temp_rd_data <= clk_div;
					end 
					1:begin
						temp_rd_data <= spi_write_data;
					end
					2:begin
						temp_rd_data <= spi_read_data;
					end
					3:begin
						temp_rd_data <= start_stop;
					end
					4:begin
						temp_rd_data <= cs_control;
					end
					default: begin
						temp_rd_data  <= 32'd0;
					end
				endcase
				end
			else
				temp_rd_data  <= 32'd0;
		end
end
//			控制状态机
localparam IDLE_S 		 = 0;
localparam WRITE_START_S = 1;
localparam WRITE_BUSY_S  = 2;
localparam WRITE_END_S   = 3;
reg[3:0] state;
// 状态转移
//		for write
always @(posedge HCLK or negedge rst) begin
	
	if(~rst)
		begin
			clk_div <= 32'd0;
			start_stop <= 32'd0;
			nCS_ctrl <= 1'b1;
			spi_data_in <= 32'd0;
			state <= IDLE_S;
			spi_read_data <= 32'd0;
			cs_control <= 32'd0;
			spi_wr_req <= 1'b0;
		end
	else
		begin
			if(cs && wr_en)
				begin
					case (waddr)
						0:begin
							clk_div <= wr_data ;
						end 
						1:begin
							spi_write_data <= wr_data ;
						end
						2:begin
							spi_read_data <= wr_data ;
						end
						3:begin
							start_stop <= wr_data ;
						end
						4:begin
							cs_control <= wr_data;
						end
						default: begin
						end
					endcase
				end
			if(spi_wr_ack)
				spi_read_data <= spi_data_out;
			nCS_ctrl <= (cs_control==32'hffff_ffff)?1'b0:1'b1;
			case (state)
				IDLE_S:begin
					if(start_stop == 32'd14114)begin
						state <= WRITE_START_S;
					end
				end 
				WRITE_START_S:begin
					start_stop <= 32'd14115;
					spi_data_in <= spi_write_data[7:0];
					spi_wr_req <= 1'b1;
					state <= WRITE_BUSY_S;
				end
				WRITE_BUSY_S:begin
					if(spi_wr_ack)begin
						state <= WRITE_END_S;
						spi_wr_req <= 1'b0;
					end
					else begin
						state <= WRITE_BUSY_S;
					end
				end
				WRITE_END_S:begin
					state <= IDLE_S;
					start_stop <= 32'd0;
				end
				default: begin
					state <= IDLE_S;
				end
			endcase
		end
end

// 状态控制
reg[31:0] temp_read_word;
reg[31:0] temp_write_word;

spi_master spi_master_m0(
	.sys_clk                        (HCLK                    ),
	.rst                            (rst                    ),
	.nCS                            (SD_nCS                 ),
	.DCLK                           (SD_DCLK                ),
	.MOSI                           (SD_MOSI                ),
	.MISO                           (SD_MISO                ),
	.clk_div                        (clk_div[15:0]          ),
	.CPOL                           (1'b1                   ),
	.CPHA                           (1'b1                   ),
	.nCS_ctrl                       (nCS_ctrl               ),
	.wr_req                         (spi_wr_req             ),
	.wr_ack                         (spi_wr_ack             ),
	.data_in                        (spi_data_in            ),
	.data_out                       (spi_data_out           ),
	.state							(spi_state				)
//  .byte_valid						(byte_valid				)
);

endmodule