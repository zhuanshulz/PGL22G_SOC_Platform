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


	wire            sd_sec_read;               //SD card sector read
	wire[31:0]      sd_sec_read_addr;          //SD card sector read address
	wire[7:0]      sd_sec_read_data;          //SD card sector read data
	wire           sd_sec_read_data_valid;    //SD card sector read data valid
	wire            sd_sec_write;              //SD card sector write
	wire[31:0]      sd_sec_write_addr;         //SD card sector write address
	wire[31:0]       sd_sec_write_data;         //SD card sector write data
	wire           sd_sec_write_data_req;     //SD card sector write data next clock is valid

assign sd_sec_read = 1'b0;
assign sd_sec_write = 1'b0;


wire[15:0]           spi_clk_div;               //SPI module clock division parameter
wire                 cmd_req;                   //SD card command request
wire                 cmd_req_ack;               //SD card command request response
wire                 cmd_req_error;             //SD card command request error
wire[47:0]           cmd;                       //SD card command
wire[7:0]            cmd_r1;                    //SD card expect response
wire[15:0]           cmd_data_len;              //SD card command read data length
wire                 block_read_valid;          //SD card sector data read data valid
wire                 block_read_req;            //SD card sector data read request//表示读完了，可以继续读了。
wire[7:0]            block_read_data;           //SD card sector data read data
wire                 block_read_req_ack;        //SD card sector data read response
wire[7:0]            block_write_data;          //SD card sector data write data next clock is valid
wire                 block_write_data_rd;       //SD card sector data write data
wire                 block_write_req_ack;       //SD card sector data write response
wire                 block_write_req;           //SD card sector data write request// 表示写完了，可以继续写了。

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

reg [31:0] TRANSDATA[127:0];			/* Offset: 0x000-0x1FF (R/W) Data Registers    *///0-127
reg [31:0] BASEADDR;					/* Offset: 0x200 (R/W) Base Address Register   *///128
reg [31:0] READEN;						/* Offset: 0x204 (R/W) Read Enable Register    *///129
reg [31:0] INITIALISED;					/* Offset: 0x208 (R/ ) Initialization Register *///130
reg [31:0] STATUS;						/* Offset: 0x20c (R/ ) showing status Register */ //eg. command execution status//131


assign SPI_LOW_SPEED_DIV = 16'd498;			 // spi clk speed = clk speed /((SPI_LOW_SPEED_DIV + 2) * 2 )
assign SPI_HIGH_SPEED_DIV = 16'd2;			 // spi clk speed = clk speed /((SPI_LOW_SPEED_DIV + 2) * 2 )

assign sd_sec_write_data = TRANSDATA[wr_data_cnt];

wire[4:0] state;

always @(posedge HCLK or negedge rst) begin
	if(~rst)
		STATUS <= 32'd0;
	else
	 	STATUS <= {25'd0,
		 sd_sec_read_end,		// 1
		 sd_sec_write_end,		// 1
		 state};				// 5 bits
end

localparam IDEL = 0;
localparam WRITE_TOKEN = 1;
localparam WRITE_DATA  = 2;
localparam WRITE_CRC   = 3;
localparam WRITE_SUC   = 4;
localparam WRITE_BUSY  = 5;
localparam WRITE_ACK   = 6;
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
reg temp_rd_data;
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
					if(rd_addr <= 22'd127)
						TRANSDATA[rd_addr] <= wr_data ;
					case (waddr)
						22'd128 : 	begin
										BASEADDR <= wr_data;
										READEN	 <= 32'd0;
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
 .run_state(state)
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