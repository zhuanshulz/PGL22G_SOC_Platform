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

//================================================================================
//  Revision History:
//  Date          By            Revision    Change Description
//--------------------------------------------------------------------------------
//  2017/7/19     meisq          1.0         Original
//*******************************************************************************/
// ?????????????????????????????????????????????????????????????????????DDR?????????index???
// ???????????????????????????????????????????????????????????????????????????index????????????
// ???????????????????????????AHB?????????????????????
module cmos_write_req_gen(
	input              rst_n,
	input              HCLK,

    // ahb interface
    input              cs,
    input              wr_en,
    input [21:0]       waddr,
    input [31:0]       wr_data,
    input              rd_en,
    input [21:0]       raddr,
    output reg [31:0]       rdata,

    input              cmos_init_done,
	input              cmos_vsync,      // ???????????????   ??????????????????????????????????????????????????????
    input              cmos_href,       // ???????????????   ??????????????????????????????1024B???????????????
    output   [31:0]    write_len,       // ???????????????????????????????????????????????????????????????
	output reg         write_req,
	output reg         write_addr_index,
	output reg         read_addr_index,
    output reg         read_enable,
	input              write_req_ack
);

reg [31:0]           init_done;              //0
reg [31:0]           read_status;         //1
reg [31:0]           write_status;         //1
reg [31:0]           read_addr;         //2
reg [31:0]           read_len;          //3     ?????????????????????????????????1024B
reg [31:0]           write_addr;        //4

//			???????????????
localparam IDLE_S 		 = 0;
localparam FRAME_START_S = 1;
localparam WRITE_BUSY_S  = 2;
localparam WRITE_END_S   = 3;
reg[3:0] wr_state;
reg [31:0]           read_len_temp;
//		for read
always @(posedge HCLK or negedge rst_n) begin
	if(~rst_n)
		begin
            rdata <= 'd0;
		end
	else
		begin
			if(cs && rd_en)	begin
				case (raddr)
					0:begin
						rdata <= init_done;
					end 
					1:begin
						rdata <= read_status;
					end
					2:begin
						rdata <= write_status;
					end
					3:begin
						rdata <= read_addr;
					end
					4:begin
						rdata <= read_len;
					end
                    5:begin
						rdata <= write_addr;
					end
					default: begin
						rdata  <= 32'd0;
					end
				endcase
				end
		end
end

//		for write
always @(posedge HCLK or negedge rst_n) begin
if(~rst_n)
    begin
        init_done <= 32'd0;
        read_status <= 'd0;
        write_status <= 'd0;
        read_addr <= 'd0;
        read_len <= 'd0;
        write_addr <= 'd0;

        write_addr_index <='d1; // ???????????????????????????1??????????????????0??????
        read_addr_index <='d0;
        read_enable <='d0;      // ??????????????????
        write_req <= 'd0;    // ?????????????????????
        read_len_temp <= 'd0;
    end
else
    begin
        if(cs && wr_en)
            begin
                case (waddr)
                    0:begin
                        init_done <= wr_data;
                    end 
                    1:begin
                        read_status <= wr_data;
                    end
                    2:begin
                        write_status <= wr_data;
                    end
                    3:begin
                        read_addr <= wr_data;
                    end
                    4:begin
                        read_len <= wr_data;
                    end
                    5:begin
                        write_addr <= wr_data;
                    end
                    default: begin
                    end
                endcase
            end
        else begin
            init_done <= cmos_init_done;

            case(wr_state)
            IDLE_S:begin
                if(vsync_posedge)begin
                    wr_state <= FRAME_START_S;
                end
                else begin
                    wr_state <= IDLE_S;
                end
            end
            FRAME_START_S:begin     // ?????????????????????????????????????????????????????????????????????????????????
                write_req <= 1'b1;
                if(write_req_ack)begin
                    wr_state <= WRITE_BUSY_S;

                    write_addr_index <= ~write_addr_index;
                    read_addr_index <= write_addr_index;
                    read_len <= read_len_temp;
                    write_req <= 1'b0;
                    read_len_temp <= 'd0;
                end
            end
            WRITE_BUSY_S:begin      // ?????????????????????????????????????????????
                if(vsync_negedge)begin   //????????????????????????,????????????????????????
                    wr_state <= WRITE_END_S;
                end
                else begin
                    wr_state <= WRITE_BUSY_S;
                    if(hsync_posedge)begin     //???????????????????????????????????????????????????
                        read_len_temp <= read_len_temp + 'd1;
                    end
                    else begin
                        read_len_temp <= read_len_temp;
                    end
                end

            end
            WRITE_END_S:begin
                wr_state <= IDLE_S;
            end
            default:begin
                
            end
            endcase
        end
    end
end


reg cmos_vsync_d0;
reg cmos_vsync_d1;
reg cmos_href_d0;
reg cmos_href_d1;
reg vsync_posedge;
reg vsync_negedge;
reg hsync_posedge;
always@(posedge HCLK or negedge rst_n)
begin
	if(rst_n == 1'b0)
	begin
		cmos_vsync_d0 <= 1'b0;
		cmos_vsync_d1 <= 1'b0;
        cmos_href_d0 <= 1'b0;
        cmos_href_d1 <= 1'b0;
	end
	else
	begin
		cmos_vsync_d0 <= cmos_vsync;
		cmos_vsync_d1 <= cmos_vsync_d0;
        cmos_href_d0 <= cmos_href;
        cmos_href_d1 <= cmos_href_d0;
	end
end
always@(posedge HCLK or negedge rst_n)
begin
	if(rst_n == 1'b0)begin
        vsync_posedge <= 'd0;
        vsync_negedge <= 'd0;
        hsync_posedge <= 'd0;
    end
	else begin
        if(cmos_vsync_d0 == 1'b1 && cmos_vsync_d1 == 1'b0)begin
            vsync_posedge <= 1'b1;
        end
        else if(cmos_vsync_d0 == 1'b0 && cmos_vsync_d1 == 1'b1)begin
            vsync_negedge <= 1'b1;
        end
        else begin
            vsync_posedge <= 1'b0;
            vsync_negedge <= 1'b0;
        end

        if(cmos_href_d0 == 1'b1 && cmos_href_d1 == 1'b0)begin
            hsync_posedge <= 1'b1;
        end
        else begin
            hsync_posedge <= 1'b0;
        end
    end
end

endmodule 
