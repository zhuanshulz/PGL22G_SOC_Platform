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


	wire           sd_init_done;              //SD card initialization is complete
	wire           sd_sec_read_end;           //SD card sector read end
	wire           sd_sec_write_end;           //SD card sector write end
	reg             sd_sec_read;               //SD card sector read
	wire[31:0]      sd_sec_read_addr;          //SD card sector read address
	reg[31:0]      sd_sec_read_addr_reg;          //SD card sector read address
	wire[7:0]      sd_sec_read_data;          //SD card sector read data
	wire           sd_sec_read_data_valid;    //SD card sector read data valid
	reg            sd_sec_write;              //SD card sector write
	reg [31:0]      sd_sec_write_addr;         //SD card sector write address
	reg[7:0]       sd_sec_write_data;         //SD card sector write data


	wire           sd_sec_write_data_req;     //SD card sector write data next clock is valid

// assign sd_sec_read = 1'b0;
// assign sd_sec_write = 1'b0;


wire[15:0]           spi_clk_div;               //SPI module clock division parameter
wire                 cmd_req;                   //SD card command request
wire                 cmd_req_ack;               //SD card command request response
wire                 cmd_req_error;             //SD card command request error
wire[47:0]           cmd;                       //SD card command
wire[7:0]            cmd_r1;                    //SD card expect response
wire[15:0]           cmd_data_len;              //SD card command read data length
wire                 block_read_valid;          //SD card sector data read data valid
wire[15:0]			 byte_count;				//SD card byte number in a sector
wire                 block_read_req;            //SD card sector data read request// 
wire[7:0]            block_read_data;           //SD card sector data read data
wire                 block_read_req_ack;        //SD card sector data read response
wire[7:0]            block_write_data;          //SD card sector data write data next clock is valid
wire                 block_write_data_rd;       //SD card sector data write data
wire                 block_write_req_ack;       //SD card sector data write response
wire                 block_write_req;           //SD card sector data write request// 写请求

wire                 nCS_ctrl;                  //SPI module chip select control
wire                 spi_wr_req;                //SPI module data sending request
wire                 spi_wr_ack;                //SPI module data request response
wire[7:0]            spi_data_in;               //SPI module send data
wire[7:0]            spi_data_out;              //SPI module data returned
wire[15:0]           clk_div;

wire[15:0]  SPI_LOW_SPEED_DIV;         // SD card low speed mode frequency division parameter,spi clk speed = clk speed /((SPI_LOW_SPEED_DIV + 2) * 2 )
wire[15:0]  SPI_HIGH_SPEED_DIV;           // SD card high speed mode frequency division parameter,spi clk speed = clk speed /((SPI_HIGH_SPEED_DIV + 2) * 2 )
wire 		byte_valid;	
wire[9:0]             wr_data_cnt;
reg [9:0]	wr_data_cnt_reg;
reg [31:0] TRANSDATA[127:0];			/* Offset: 0x000-0x1FF (R/W) Data Registers    *///0-127
reg [31:0] BASEADDR;					/* Offset: 0x200 (R/W) Base Address Register   *///128
reg [31:0] READEN;						/* Offset: 0x204 (R/W) Read Enable Register    *///129
reg [31:0] INITIALISED;					/* Offset: 0x208 (R/ ) Initialization Register *///130
reg [31:0] STATUS;						/* Offset: 0x20c (R/ ) showing status Register */ //eg. command execution status//131



assign SPI_LOW_SPEED_DIV = 16'd498;			 // spi clk speed = clk speed /((SPI_LOW_SPEED_DIV + 2) * 2 )
assign SPI_HIGH_SPEED_DIV = 16'd2;			 // spi clk speed = clk speed /((SPI_LOW_SPEED_DIV + 2) * 2 )

wire[4:0] sd_card_state;
reg[15:0] write_count;


// always @(posedge HCLK or negedge rst) begin
// 	if(~rst)
// 		STATUS <= 32'd0;
// 	else
// 		STATUS <= {};
// end

always @(posedge HCLK or negedge rst) begin
	if(~rst)
		INITIALISED<=32'd0;
	else
		INITIALISED <= {31'd0,sd_init_done};
end
reg[31:0] temp_rd_data;
assign rd_data = temp_rd_data;//(rd_addr[2:0]==3'b000)?INITIALISED:(rd_addr[2:0]==3'b010)?32'hff:32'h1313;


//		for read
always @(posedge HCLK or negedge rst) begin
	if(~rst)
		begin
			temp_rd_data  <= 32'd0;
		end
	else
		begin
			if(cs && rd_en)
				begin
					if(rd_addr <= 22'd127)
						temp_rd_data <= TRANSDATA[rd_addr];
					else 
					case (rd_addr)
						22'd128 : temp_rd_data <= BASEADDR;
						22'd129 : temp_rd_data <= READEN;
						22'd130 : temp_rd_data <= INITIALISED;
						22'd131 : temp_rd_data <= STATUS;
						default: temp_rd_data  <= 32'd0;
					endcase
				end
			else
				temp_rd_data  <= 32'd0;
		end
end

//		for write
always @(posedge HCLK or negedge rst) begin
	
	if(~rst)
		begin
			BASEADDR  <= 32'd0;
			READEN <= 32'd0;
		end
	else
		begin
			if(cs && wr_en)
				begin
					case (waddr)
						22'd128 : 	begin
										BASEADDR <= wr_data;
									end
						22'd129 : 	begin
										READEN <= wr_data;
									end
						// 22'd130 : INITIALISED <= wr_data;		//read only
						// 22'd131 : STATUS <= wr_data;			//read only
						default: ;
					endcase
				end
		end
end
//			控制状态机
localparam IDLE_S 		 = 0;
localparam WRITE_START_S = 1;
localparam WRITE_BUSY_S  = 2;
localparam WRITE_END_S   = 3;
localparam READ_START_S  = 4;
localparam READ_BUSY_S   = 5;
localparam READ_END_S    = 6;
reg[3:0] state;
// 状态转移
wire write_start;
wire read_start;
assign write_start = STATUS[9];
assign read_start = STATUS[8];
always @(posedge HCLK or negedge rst) begin
	if(~rst)begin
			state <= IDLE_S;
		end
	else begin
		case (state)
			IDLE_S:begin
				state <= write_start?WRITE_START_S:read_start?READ_START_S:IDLE_S;
			end 
			WRITE_START_S:begin
				state <= WRITE_BUSY_S;
			end 
			WRITE_BUSY_S:begin
				if(sd_sec_write_end)
					state <= WRITE_END_S;
			end 
			WRITE_END_S:begin
				state <=IDLE_S;
			end 
			READ_START_S:begin
				state <= READ_BUSY_S;
			end 
			READ_BUSY_S:begin
				if(sd_sec_read_end)
					state <= READ_END_S;
			end 
			READ_END_S:begin
				state <=IDLE_S;
			end 
			default: begin
				state <=IDLE_S;
			end
		endcase
	end
end

// 状态控制
reg[31:0] temp_read_word;
reg[31:0] temp_write_word;
integer i=0;

always @(posedge HCLK or negedge rst) begin
	if(~rst)begin
			sd_sec_read  <= 1'b0;
			sd_sec_write <= 1'b0;
			STATUS <= 32'd0;
			write_count <= 16'd0;
			sd_sec_write_addr <='d0;
			sd_sec_read_addr_reg <= 'd0;
		end
	else begin
		if(cs && wr_en)begin
			if( waddr == 22'd131)
				STATUS <= wr_data;
			else if( waddr <= 22'd127)
				TRANSDATA[waddr[7:0]] <= wr_data;
		end
		else case (state)
			IDLE_S:begin
				sd_sec_read <= 1'b0;
				sd_sec_write <= 1'b0;
				STATUS <= STATUS&{18'h3ffff,
				1'b0,						//write_end
				1'b0,						//read_end
				1'b0,						//write_busy
				1'b0,						//read_busy
				1'b0,						//write_start
				1'b0,						//read_start
				3'd0,						//reserved
		 		sd_card_state};				// 5 bits
			end 
			WRITE_START_S:begin
				STATUS <= STATUS|{18'd0,
				1'b0,						//write_end
				1'b0,						//read_end
				1'b1,						//write_busy
				1'b0,						//read_busy
				1'b1,						//write_start
				1'b0,						//read_start
				3'd0,						//reserved
		 		sd_card_state};				// 5 bits
				sd_sec_write_addr <= BASEADDR;
				sd_sec_write <= 1'b1;
			end 
			WRITE_BUSY_S:begin
				STATUS <= STATUS&{18'h3ffff,
				1'b1,						//write_end
				1'b1,						//read_end
				1'b1,						//write_busy
				1'b1,						//read_busy
				1'b1,						//write_start
				1'b1,						//read_start
				3'b111,						//reserved
		 		sd_card_state};				// 5 bits
				if(sd_sec_write_data_req)begin
					temp_write_word = TRANSDATA[(wr_data_cnt-10'd1)>>2];
					case(wr_data_cnt[1:0])
					2'b00:begin
						sd_sec_write_data <= temp_write_word[31:24];
					end
					2'b01:begin
						sd_sec_write_data <= temp_write_word[7:0];
					end
					2'b10:begin
						sd_sec_write_data <= temp_write_word[15:8];
					end
					2'b11:begin
						sd_sec_write_data <= temp_write_word[23:16];
					end
					default:begin
						sd_sec_write_data <= 8'd0;
					end
					endcase
				end

			end 
			WRITE_END_S:begin
				STATUS <= STATUS&{18'h3ffff,
				1'b1,						//write_end
				1'b0,						//read_end
				1'b0,						//write_busy
				1'b0,						//read_busy
				1'b0,						//write_start
				1'b0,						//read_start
				3'd0,						//reserved
		 		sd_card_state};				// 5 bits
			end 
			READ_START_S:begin	//将read busy 和 read start置为1
				STATUS <= STATUS|{18'd0,
				1'b0,						//write_end
				1'b0,						//read_end
				1'b0,						//write_busy
				1'b1,						//read_busy
				1'b0,						//write_start
				1'b1,						//read_start
				3'd0,						//reserved
		 		sd_card_state};				// 5 bits
				sd_sec_read_addr_reg <= BASEADDR;
				sd_sec_read <= 1'b1;
			end 
			READ_BUSY_S:begin	//读取数据
				STATUS <= STATUS&{18'h3ffff,
				1'b1,						//write_end
				1'b1,						//read_end
				1'b1,						//write_busy
				1'b1,						//read_busy
				1'b1,						//write_start
				1'b1,						//read_start
				3'b111,						//reserved
		 		sd_card_state};				// 5 bits
				 
				if(sd_sec_read_data_valid)
				begin
					temp_read_word <= {temp_read_word[23:0],sd_sec_read_data};
					if((byte_count[1:0] == 2'b00)&&(byte_count != 16'd0))
					begin
						for(i=0;i<127;i=i+1) begin
							TRANSDATA[i+1] = TRANSDATA[i];
						end
						TRANSDATA[0] = temp_read_word;
					end
				end
			end 
			READ_END_S:begin
				STATUS <= STATUS&{18'h3ffff,
				1'b1,						//write_end
				1'b1,						//read_end
				1'b0,						//write_busy
				1'b0,						//read_busy
				1'b0,						//write_start
				1'b0,						//read_start
				3'd0,						//reserved
		 		sd_card_state};				// 5 bits
			end 
			default: begin
				
			end
		endcase
	end
end
assign sd_sec_read_addr = sd_sec_read_addr_reg;

sd_card_sec_read_write sd_card_sec_read_write_m0(
	.clk                            (HCLK                    ),
	.rst                            (rst                    ),
	.sd_init_done                   (sd_init_done           ),
	.sd_sec_read                    (sd_sec_read            ),
	.sd_sec_read_addr               (sd_sec_read_addr       ),
	.sd_sec_read_data               (sd_sec_read_data       ),
	.sd_sec_read_data_valid         (sd_sec_read_data_valid ),
	.sd_sec_read_end                (sd_sec_read_end        ),
	.sd_sec_write                   (sd_sec_write           ),
	.sd_sec_write_addr              (sd_sec_write_addr      ),
	.sd_sec_write_data              (sd_sec_write_data      ),
	.sd_sec_write_data_req          (sd_sec_write_data_req  ),
	.sd_sec_write_end               (sd_sec_write_end       ),
	.spi_clk_div                    (spi_clk_div            ),
	.cmd_req                        (cmd_req                ),
	.cmd_req_ack                    (cmd_req_ack            ),
	.cmd_req_error                  (cmd_req_error          ),
	.cmd                            (cmd                    ),
	.cmd_r1                         (cmd_r1                 ),
	.cmd_data_len                   (cmd_data_len           ),
	.block_read_req                 (block_read_req         ),
	.block_read_valid               (block_read_valid       ),
	.block_read_data                (block_read_data        ),
	.block_read_req_ack             (block_read_req_ack     ),
	.block_write_req                (block_write_req        ),
	.block_write_data               (block_write_data       ),
	.block_write_data_rd            (block_write_data_rd    ),
	.block_write_req_ack            (block_write_req_ack    ),

    .SPI_LOW_SPEED_DIV(SPI_LOW_SPEED_DIV),
	.SPI_HIGH_SPEED_DIV(SPI_HIGH_SPEED_DIV),
 .run_state(sd_card_state)
);

sd_card_cmd sd_card_cmd_m0(
	.sys_clk                        (HCLK                    ),
	.rst                            (rst                    ),
	.spi_clk_div                    (spi_clk_div            ),
	.cmd_req                        (cmd_req                ),
	.cmd_req_ack                    (cmd_req_ack            ),
	.cmd_req_error                  (cmd_req_error          ),
	.cmd                            (cmd                    ),
	.cmd_r1                         (cmd_r1                 ),
	.cmd_data_len                   (cmd_data_len           ),
	.block_read_req                 (block_read_req         ),
	.block_read_req_ack             (block_read_req_ack     ),
	.block_read_data                (block_read_data        ),
	.block_read_valid               (block_read_valid       ),
	.byte_count						(byte_count				),
	.block_write_req                (block_write_req        ),
	.block_write_data               (block_write_data       ),
	.block_write_data_rd            (block_write_data_rd    ),
	.block_write_req_ack            (block_write_req_ack    ),
	.nCS_ctrl                       (nCS_ctrl               ),
	.clk_div                        (clk_div                ),
	.spi_wr_req                     (spi_wr_req             ),
	.spi_wr_ack                     (spi_wr_ack             ),
	.spi_data_in                    (spi_data_in            ),
	.spi_data_out                   (spi_data_out           ),
	.wr_data_cnt					(wr_data_cnt			)

);

spi_master spi_master_m0(
	.sys_clk                        (HCLK                    ),
	.rst                            (rst                    ),
	.nCS                            (SD_nCS                 ),
	.DCLK                           (SD_DCLK                ),
	.MOSI                           (SD_MOSI                ),
	.MISO                           (SD_MISO                ),
	.clk_div                        (clk_div                ),
	.CPOL                           (1'b1                   ),
	.CPHA                           (1'b1                   ),
	.nCS_ctrl                       (nCS_ctrl               ),
	.wr_req                         (spi_wr_req             ),
	.wr_ack                         (spi_wr_ack             ),
	.data_in                        (spi_data_in            ),
	.data_out                       (spi_data_out           )
//  .byte_valid						(byte_valid				)
);

endmodule