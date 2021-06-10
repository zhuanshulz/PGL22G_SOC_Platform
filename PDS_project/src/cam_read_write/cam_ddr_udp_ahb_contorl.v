module cam_ddr_udp_ahb_contorl(
	input              rst,
	input              pclk,
    
    /*              cmos signals        */
    input               cmos_pclk,
    input               cmos_href,
    input               cmos_vsync,
    input [7:0]         cmos_data,
    input               cmos_init_done,
    output reg          cmos1_xclk,
    inout               cmos1_scl,          //cmos i2c clock
    inout               cmos1_sda,          //cmos i2c data

    /*------------- udp speedup module interface --------*/
    output [7:0]        udp_speedup_data,
    output              udp_speedup_data_valid,
    input               udp_speedup_data_ready,

    /*------------ ahb interface ---------------*/
    input              cs,
    input              wr_en,
    input [21:0]       waddr,
    input [31:0]       wdata,
    input              rd_en,
    input [21:0]       raddr,
    input [31:0]       rdata,

    /*------------- ddr3 axi interface ------------*/
    //AXI WRITE
    output reg [31:0] awaddr_1,
    output reg        awvalid_1,
    input             awready_1,
    output reg [63:0] wdata_1,
    output reg        wlast_1,
    output reg        wvalid_1,
    input             wready_1,
                      
    //AXI READ        
    output reg [31:0] araddr_1,
    output reg        arvalid_1,
    input             arready_1,
    input      [63:0] rdata_1,
    input             rlast_1,
    input             rvalid_1,
    output reg        rready_1
);


//I2C master controller     //以下两个模块负责对CMOS图像进行初始化
wire[9:0]                   cmos1_lut_index;
wire[31:0]                  cmos1_lut_data;
i2c_config i2c_config_m0(
	.rst                        (rst                   ),
	.clk                        (HCLK                  ),
	.clk_div_cnt                (16'd500                  ),
	.i2c_addr_2byte             (1'b1                     ),
	.lut_index                  (cmos1_lut_index          ),
	.lut_dev_addr               (cmos1_lut_data[31:24]    ),
	.lut_reg_addr               (cmos1_lut_data[23:8]     ),
	.lut_reg_data               (cmos1_lut_data[7:0]      ),
	.error                      (                         ),
	.done                       (done_init_coms1          ),
	.i2c_scl                    (cmos1_scl                ),
	.i2c_sda                    (cmos1_sda                )
);
//configure look-up table
lut_ov5640_rgb565_800_600 lut_ov5640_rgb565_800_600_m0(
	.lut_index                  (cmos1_lut_index          ),
	.lut_data                   (cmos1_lut_data           )
);




always @(posedge HCLK or posedge rst)begin
    if( rst )begin
        cmos1_xclk <= 1'b0;
        end
    else begin
        cmos1_xclk <= ~cmos1_xclk;
    end
end

wire       cmos_vsync_delay;
wire       cmos_href_delay;
wire [7:0] cmos_data_delay;

camera_delay camera_delay_inst
(
   .cmos_pclk          (cmos_pclk),              //cmos pxiel clock
   .cmos_href          (cmos_href),              //cmos hsync refrence
   .cmos_vsync         (cmos_vsync),             //cmos vsync
   .cmos_data          (cmos_data),              //cmos data

   .cmos_href_delay    (cmos_href_delay),              //cmos hsync refrence
   .cmos_vsync_delay   (cmos_vsync_delay),             //cmos vsync
   .cmos_data_delay    (cmos_data_delay)             //cmos data
) ;

//////////////////// CMOS FIFO/////////////////// 
wire [10 : 0] fifo_data_count;
wire [7:0] fifo_data;
wire fifo_rd_en;
camera_fifo camera_fifo_inst(       // 这个是写缓存
    .wr_clk(cmos_pclk),
    .wr_rst(cmos_vsync),
    .wr_en(cmos_href_delay),
    .wr_data(cmos_data_delay),
    .wr_full(),
    .wr_water_level(),
    .almost_full(),
    .rd_clk(gmii_rx_clk),
    .rd_rst(cmos_vsync),
    .rd_en(fifo_rd_en),
    .rd_data(fifo_data),
    .rd_empty(),
    .rd_water_level(fifo_data_count),
    .almost_empty());

assign udp_speedup_data_valid = udp_speedup_data_ready?(fifo_data_count!=0):1'b0;
assign udp_speedup_data = fifo_data;
assign fifo_rd_en = udp_speedup_data_ready;


// frame_fifo_write #(             // 这个模块负责把一幅图像写进DDR
// 	.MEM_DATA_BITS              (MEM_DATA_BITS            ),
// 	.ADDR_BITS                  (ADDR_BITS                ),
// 	.BUSRT_BITS                 (BUSRT_BITS               ),
// 	.BURST_SIZE                 (BURST_SIZE               )) 
//     frame_fifo_write_m0 (  
// 	.rst                        (rst                      ),
// 	.mem_clk                    (mem_clk                  ),
// 	.wr_burst_req               (wr_burst_req             ),
// 	.wr_burst_len               (wr_burst_len             ),
// 	.wr_burst_addr              (wr_burst_addr            ),
// 	.wr_burst_data_req          (wr_burst_data_req        ),
// 	.wr_burst_finish            (wr_burst_finish          ),
// 	.write_req                  (write_req                ),
// 	.write_req_ack              (write_req_ack            ),
// 	.write_finish               (write_finish             ),
// 	.write_addr_0               (write_addr_0             ),
// 	.write_addr_1               (write_addr_1             ),
// 	.write_addr_2               (write_addr_2             ),
// 	.write_addr_3               (write_addr_3             ),
// 	.write_addr_index           (write_addr_index         ),    
// 	.write_len                  (write_len                ),
// 	.fifo_aclr                  (write_fifo_aclr          ),
// 	.rdusedw                    (rdusedw                  ) 	
// );

// cmos_write_req_gen  u_cmos_write_req_gen (              // 这个负责生成index，并和AHB通信
//     .rst_n                   ( rst_n              ),
//     .pclk                    ( pclk               ),
//     .cs                      ( cs                 ),
//     .wr_en                   ( wr_en              ),
//     .waddr                   ( waddr              ),
//     .wdata                   ( wdata              ),
//     .rd_en                   ( rd_en              ),
//     .raddr                   ( raddr              ),
//     .rdata                   ( rdata              ),
//     .cmos_init_done          ( cmos_init_done     ),
//     .cmos_vsync              ( cmos_vsync         ),
//     .cmos_href               ( cmos_href          ),
//     .write_req_ack           ( write_req_ack      ),

//     .write_len               ( write_len          ),
//     .write_req               ( write_req          ),
//     .write_addr_index        ( write_addr_index   ),
//     .read_addr_index         ( read_addr_index    ),
//     .read_enable             ( read_enable        )
// );


// frame_fifo_read #(              // 这个模块负责把一幅图像读出来，后面再接一个FIFO
// 	.MEM_DATA_BITS              (MEM_DATA_BITS            ),
// 	.ADDR_BITS                  (ADDR_BITS                ),
// 	.BUSRT_BITS                 (BUSRT_BITS               ),
// 	.FIFO_DEPTH                 (128                      ),
// 	.BURST_SIZE                 (BURST_SIZE               ))
//     frame_fifo_read_m0(
// 	.rst                        (rst                      ),
// 	.mem_clk                    (mem_clk                  ),
// 	.rd_burst_req               (rd_burst_req             ),   
// 	.rd_burst_len               (rd_burst_len             ),  
// 	.rd_burst_addr              (rd_burst_addr            ),
// 	.rd_burst_data_valid        (rd_burst_data_valid      ),    
// 	.rd_burst_finish            (rd_burst_finish          ),
// 	.read_req                   (read_req                 ),
// 	.read_req_ack               (read_req_ack             ),
// 	.read_finish                (read_finish              ),
// 	.read_addr_0                (read_addr_0              ),
// 	.read_addr_1                (read_addr_1              ),
// 	.read_addr_2                (read_addr_2              ),
// 	.read_addr_3                (read_addr_3              ),
// 	.read_addr_index            (read_addr_index          ),    
// 	.read_len                   (read_len                 ),
// 	.fifo_aclr                  (read_fifo_aclr           ),
// 	.wrusedw                    (wrusedw                  )
// );
// // 还差一个读出FIFO，并且修改读出触发逻辑


// // 这个模块负责将读写请求转换成DDR的AXI接口信号。
// aq_axi_master_cam  u_aq_axi_master_cam (
//     .ARESETN                 ( ARESETN          ),
//     .ACLK                    ( ACLK             ),
//     .M_AXI_AWREADY           ( M_AXI_AWREADY    ),
//     .M_AXI_WREADY            ( M_AXI_WREADY     ),
//     .M_AXI_BID               ( M_AXI_BID        ),
//     .M_AXI_BRESP             ( M_AXI_BRESP      ),
//     .M_AXI_BUSER             ( M_AXI_BUSER      ),
//     .M_AXI_BVALID            ( M_AXI_BVALID     ),
//     .M_AXI_ARREADY           ( M_AXI_ARREADY    ),
//     .M_AXI_RID               ( M_AXI_RID        ),
//     .M_AXI_RDATA             ( M_AXI_RDATA      ),
//     .M_AXI_RRESP             ( M_AXI_RRESP      ),
//     .M_AXI_RLAST             ( M_AXI_RLAST      ),
//     .M_AXI_RUSER             ( M_AXI_RUSER      ),
//     .M_AXI_RVALID            ( M_AXI_RVALID     ),
//     .MASTER_RST              ( MASTER_RST       ),
//     .WR_START                ( WR_START         ),
//     .WR_ADRS                 ( WR_ADRS          ),
//     .WR_LEN                  ( WR_LEN           ),
//     .WR_FIFO_EMPTY           ( WR_FIFO_EMPTY    ),
//     .WR_FIFO_AEMPTY          ( WR_FIFO_AEMPTY   ),
//     .WR_FIFO_DATA            ( WR_FIFO_DATA     ),
//     .RD_START                ( RD_START         ),
//     .RD_ADRS                 ( RD_ADRS          ),
//     .RD_LEN                  ( RD_LEN           ),
//     .RD_FIFO_FULL            ( RD_FIFO_FULL     ),
//     .RD_FIFO_AFULL           ( RD_FIFO_AFULL    ),

//     .M_AXI_AWID              ( M_AXI_AWID       ),
//     .M_AXI_AWADDR            ( M_AXI_AWADDR     ),
//     .M_AXI_AWLEN             ( M_AXI_AWLEN      ),
//     .M_AXI_AWSIZE            ( M_AXI_AWSIZE     ),
//     .M_AXI_AWBURST           ( M_AXI_AWBURST    ),
//     .M_AXI_AWLOCK            ( M_AXI_AWLOCK     ),
//     .M_AXI_AWCACHE           ( M_AXI_AWCACHE    ),
//     .M_AXI_AWPROT            ( M_AXI_AWPROT     ),
//     .M_AXI_AWQOS             ( M_AXI_AWQOS      ),
//     .M_AXI_AWUSER            ( M_AXI_AWUSER     ),
//     .M_AXI_AWVALID           ( M_AXI_AWVALID    ),
//     .M_AXI_WDATA             ( M_AXI_WDATA      ),
//     .M_AXI_WSTRB             ( M_AXI_WSTRB      ),
//     .M_AXI_WLAST             ( M_AXI_WLAST      ),
//     .M_AXI_WUSER             ( M_AXI_WUSER      ),
//     .M_AXI_WVALID            ( M_AXI_WVALID     ),
//     .M_AXI_BREADY            ( M_AXI_BREADY     ),
//     .M_AXI_ARID              ( M_AXI_ARID       ),
//     .M_AXI_ARADDR            ( M_AXI_ARADDR     ),
//     .M_AXI_ARLEN             ( M_AXI_ARLEN      ),
//     .M_AXI_ARSIZE            ( M_AXI_ARSIZE     ),
//     .M_AXI_ARBURST           ( M_AXI_ARBURST    ),
//     .M_AXI_ARLOCK            ( M_AXI_ARLOCK     ),
//     .M_AXI_ARCACHE           ( M_AXI_ARCACHE    ),
//     .M_AXI_ARPROT            ( M_AXI_ARPROT     ),
//     .M_AXI_ARQOS             ( M_AXI_ARQOS      ),
//     .M_AXI_ARUSER            ( M_AXI_ARUSER     ),
//     .M_AXI_ARVALID           ( M_AXI_ARVALID    ),
//     .M_AXI_RREADY            ( M_AXI_RREADY     ),
//     .WR_READY                ( WR_READY         ),
//     .WR_FIFO_RE              ( WR_FIFO_RE       ),
//     .WR_DONE                 ( WR_DONE          ),
//     .RD_READY                ( RD_READY         ),
//     .RD_FIFO_WE              ( RD_FIFO_WE       ),
//     .RD_FIFO_DATA            ( RD_FIFO_DATA     ),
//     .RD_DONE                 ( RD_DONE          ),
//     .DEBUG                   ( DEBUG            )
// );

endmodule