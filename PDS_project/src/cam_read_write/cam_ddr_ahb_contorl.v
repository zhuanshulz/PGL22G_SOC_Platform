// 该模块负责将CAM数据通过AXI接口传入DDR，并且传输逻辑受软核控制，接入AHB-MEM接口。

module cam_ddr_ahb_contorl(
    
    /*              cmos signals        */
    input  [11 : 0]            fifo_data_count,
    input [7:0]              fifo_data,
    output              fifo_rd_en,
    input               cmos_init_done,

    /*------------ ahb interface ---------------*/
    input               HCLK,
    input              cs,
	input              rst,
    input              wr_en,
    input [21:0]       waddr,
    input [31:0]       wr_data,
    input              rd_en,
    input [21:0]       rd_addr,
    input [31:0]       rd_data,

    /*------------- ddr3 axi interface ------------*/
    //AXI WRITE
	input              aclk,
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



frame_fifo_write #(             // 这个模块负责把一幅图像写进DDR
	.MEM_DATA_BITS              (8            ),
	.ADDR_BITS                  (12                ),
	.BUSRT_BITS                 (8               ),
	.BURST_SIZE                 (1024               )) 
    frame_fifo_write_m0 (  
	.rst                        (rst                      ),    //input
	.mem_clk                    (aclk                      ),    //input
	.wr_burst_req               (wr_burst_req             ),    //output
	.wr_burst_len               (wr_burst_len             ),    //output
	.wr_burst_addr              (wr_burst_addr            ),    //output
	.wr_burst_finish            (wr_burst_finish          ),    //input
	.write_req                  (write_req                ),    //input
	.write_req_ack              (write_req_ack            ),    //output
	.write_finish               (write_finish             ),    //output
	.write_addr_0               (write_addr_0             ),    //input
	.write_addr_1               (write_addr_1             ),    //input

	.write_addr_index           (write_addr_index         ),    //input
	.write_len                  (write_len                ),    //input
	.rdusedw                    (rdusedw                  ) 	    //input
);

cmos_write_req_gen  u_cmos_write_req_gen (              // 这个负责生成index，并和AHB通信
    .rst_n                   ( rst_n              ),
    .HCLK                    ( HCLK               ),
    .cs                      ( cs                 ),
    .wr_en                   ( wr_en              ),
    .waddr                   ( waddr              ),
    .wr_data                   ( wr_data              ),
    .rd_en                   ( rd_en              ),
    .raddr                   ( rd_addr              ),
    .rdata                   ( rd_data              ),
    .cmos_init_done          ( cmos_init_done     ),
    .cmos_vsync              ( cmos_vsync         ),
    .cmos_href               ( cmos_href          ),
    .write_req_ack           ( write_req_ack      ),

    .write_len               ( write_len          ),
    .write_req               ( write_req          ),
    .write_addr_index        ( write_addr_index   ),
    .read_addr_index         ( read_addr_index    ),
    .read_enable             ( read_enable        )
);


// 现在暂时不需要读，因为UDP加速模块的发送还存在校验和错误的情况。所以这一版本还是通过ARM核进行发送处理
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