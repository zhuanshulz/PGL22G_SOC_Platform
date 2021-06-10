module m1_soc_top (
	input             ex_clk_50m,
	input             rst_key,
    input             gpio_in0,
    input             gpio_in1,
//debug
//    input             pad_nTRST,
//    input             pad_nRST,    
//    input             pad_TCK,
//    input             pad_TMS,  
//    input             pad_TDI,  
//    output            pad_TDO, 

    output  [3:0]     LED,
//    output  [7:0]     gpio_out,

    input             RX,
    output            TX,

    output            spi0_clk,
    output            spi0_cs,
    output            spi0_mosi,
    input             spi0_miso,

    // output            spi1_clk,
    // output            spi1_cs,
    // output            spi1_mosi,
    // input             spi1_miso,

//COMS
inout                       cmos_scl,          //cmos i2c clock
inout                       cmos_sda,          //cmos i2c data
input                       cmos_vsync,        //cmos vsync
input                       cmos_href,         //cmos hsync refrence,data valid
input                       cmos_pclk,         //cmos pxiel clock
input   [7:0]               cmos_db,           //cmos data
output  reg                    cmos_xclk,


    inout             i2c0_sck,
    inout             i2c0_sda,

	input  		      pad_loop_in,
    input  		      pad_loop_in_h,
    output 		      pad_rstn_ch0,
    output 		      pad_ddr_clk_w,
    output 		      pad_ddr_clkn_w,
    output 		      pad_csn_ch0,
    output [15:0]     pad_addr_ch0,
    inout  [16-1:0]   pad_dq_ch0,
    inout  [16/8-1:0] pad_dqs_ch0,
    inout  [16/8-1:0] pad_dqsn_ch0,
    output [16/8-1:0] pad_dm_rdqs_ch0,
    output 		      pad_cke_ch0,
    output 		      pad_odt_ch0,
    output 		      pad_rasn_ch0,
    output 		      pad_casn_ch0,
    output 		      pad_wen_ch0,
    output [2:0]      pad_ba_ch0,
    output 		      pad_loop_out,
    output 		      pad_loop_out_h,

    // output            phy_rst_n,        
    input             rx_clki,          
    input             phy_rx_dv,        
    input             phy_rxd0,         
    input             phy_rxd1,         
    input             phy_rxd2,         
    input             phy_rxd3,         

    output            l0_sgmii_clk_shft,
    output            phy_tx_en,        
    output            phy_txd0,         
    output            phy_txd1,         
    output            phy_txd2,         
    output            phy_txd3,

    //	SPI interface 
	output           SD_nCS,                    //SD card chip select (SPI mode)
	output           SD_DCLK,                   //SD card clock
	output           SD_MOSI,                   //SD card controller data output
	input            SD_MISO                   //SD card controller data input
//    output            a/* synthesis syn_keep = 1 */,
//    output            b/* synthesis syn_keep = 1 */
); 

    `ifdef SIMULATION
        `include "../bench/src/m1_core/cm1_option_defs.v"
    `else
        `include "m1_core/cm1_option_defs.v"
    `endif

    parameter TH_1S = 27'd33000000;

    reg [26:0] cnt;
    reg heart_beat_led;

    wire              HCLK;           // AHB Memory clock
    wire              HREADYOUT;      // AHB Memory ready
    wire              HRESP;          // AHB Memory response
    wire   [31:0]     HRDATA;         // AHB Memory read data bus
    wire              HSEL;           // AHB Memory select
    wire   [1:0]      HTRANS;         // AHB Memory transaction type
    wire   [2:0]      HBURST;         // AHB Memory burst information
    wire   [3:0]      HPROT;          // AHB Memory protection control
    wire   [2:0]      HSIZE;          // AHB Memory transfer size
    wire              HWRITE;         // AHB Memory transfer direction
    wire              HMASTLOCK;      // AHB Memory locked transfer
    wire   [31:0]     HADDR;          // AHB Memory transfer address
    wire   [31:0]     HWDATA;         // AHB Memory write data bus
    wire              HREADY;         // AHB Memory bus ready   
    wire   [31:0]     HRDATAmux;                 

    wire   [11:0]     PADDR;   
    wire              PWRITE;  
    wire   [31:0]     PWDATA;  
    wire              PENABLE; 
    wire              PSEL;    
    wire   [31:0]     PRDATA;  
    wire              PREADY; 
    wire              PSLVERR;

//    reg [9:0] cnt_r = {10{1'b0}};
//    reg       error_flag;
//    
//    always @(posedge HCLK)
//    begin
//	    if (~HREADY) cnt_r <= cnt_r + 1'd1;	
//        else cnt_r <= {10{1'b0}};
//	    error_flag <= (cnt_r >= 511); 
//    end
//
//    assign a = |HADDR && HREADY && |HTRANS && |HRDATAmux && |HWDATA && |HWRITE && |HSIZE && error_flag &&
//               |PADDR && PWRITE && |PWDATA && PENABLE && PSEL && |PRDATA && PREADY;        
//
//    assign b =  |araddr_1 && arvalid_1 && arready_1 && |rdata_1 && rlast_1 && rvalid_1 && rready_1;   

    wire   [15:0]     p0_in;          // GPIO 0 inputs
    wire   [15:0]     p0_out;         // GPIO 0 outputs
    wire   [15:0]     p0_outen;       // GPIO 0 output enables
    wire   [15:0]     p0_altfunc;     // GPIO 0 alternate function (pin mux)
                     
    wire              watchdog_reset;
                     
    wire   [31:0]     wdata;
    wire   [21:0]     waddr;
    wire              w_en;
    wire   [31:0]     rdata;
    wire   [21:0]     raddr;
    wire              r_en;
    wire   [15:0]     mem_cs;
              
    wire   [7:0]      tsmac_tdata;
    wire              tsmac_tstart;
    wire              tsmac_tpnd;
    wire              tsmac_tlast;

    wire   [7:0]      tsmac_rdata;
    wire              tsmac_rvalid;
    wire              tsmac_rlast;
       
    //AXI WRITE
    wire              pll_pclk;
    wire              ddr_pll_lock;
    wire              ddrphy_rst_done;
    wire              ddrc_init_done;
                      
    wire              aclk_mux;
    wire   [31:0]     awaddr_mux;
    wire   [7:0]      awlen_mux;
    wire              awvalid_mux;
    wire              awready_mux;
    wire   [127:0]    wdata_mux;
    wire   [15:0]     wstrb_mux;
    wire              wlast_mux;
    wire              wvalid_mux;
    wire              wready_mux;
                      
    //AXI RAD         
    wire   [31:0]     araddr_mux;
    wire   [7:0]      arlen_mux;
    wire              arvalid_mux;
    wire              arready_mux;
    wire   [127:0]    rdata_mux;
    wire              rlast_mux;
    wire              rvalid_mux;
    wire              rready_mux;

    wire              aclk_1;
    wire   [31:0]     awaddr_1;
    wire              awvalid_1;
    wire              awready_1;
    wire   [63:0]     wdata_1;
    wire              wlast_1;
    wire              wvalid_1;
    wire              wready_1;
                      
    //AXI RAD         
    wire   [31:0]     araddr_1;
    wire              arvalid_1;
    wire              arready_1;
    wire   [63:0]     rdata_1;
    wire              rlast_1;
    wire              rvalid_1;
    wire              rready_1;
   
    wire              tsmac_phy_pselx;
    wire              tsmac_phy_pwrite;
    wire              tsmac_phy_penable;
    wire   [7:0]      tsmac_phy_paddr;
    wire   [31:0]     tsmac_phy_pwdata;
                      
    wire              tsmac_phy_mdo;
    wire              tsmac_phy_mdoen;
    wire              tsmac_phy_mdi;
    wire              tsmac_phy_mdio;
                      
    wire   [3:0]      phy_txd;
    wire   [3:0]      phy_rxd;

    wire   [7:0]      m1_tdata;
    wire              m1_tstart;
    wire              m1_tpnd;
    wire              m1_tlast;

    wire   [9:0]      ethernet_fifo_rd_data;
    wire   [9:0]      tsmac_fifo_wr_data;

    wire              HREADYOUT_udp;
    wire              HRESP_udp;
    wire   [31:0]     HRDATA_udp;

    wire   [7:0]      udp_tdata;
    wire              udp_tstart;
    wire              udp_tpnd;
    wire              udp_tlast;

    wire              udp_cs;


always @(posedge ex_clk_50m or negedge SYSRESETn)begin
    if( ~SYSRESETn )begin
        cmos_xclk <= 1'b0;
        end
    else begin
        cmos_xclk <= ~cmos_xclk;
    end
end
//I2C master controller     //以下两个模块负责对CMOS图像进行初始化
wire[9:0]                   cmos_lut_index;
wire[31:0]                  cmos_lut_data;
i2c_config i2c_config_m0(
	.rst                        (~SYSRESETn               ),
	.clk                        (ex_clk_50m               ),
	.clk_div_cnt                (16'd500                  ),
	.i2c_addr_2byte             (1'b1                     ),
	.lut_index                  (cmos_lut_index          ),
	.lut_dev_addr               (cmos_lut_data[31:24]    ),
	.lut_reg_addr               (cmos_lut_data[23:8]     ),
	.lut_reg_data               (cmos_lut_data[7:0]      ),
	.error                      (                         ),
	.done                       (init_done            ),
	.i2c_scl                    (cmos_scl                ),
	.i2c_sda                    (cmos_sda                )
);
//configure look-up table
lut_ov5640_rgb565_800_600 lut_ov5640_rgb565_800_600_m0(
	.lut_index                  (cmos_lut_index          ),
	.lut_data                   (cmos_lut_data           )
);
wire       cmos_vsync_delay;
wire       cmos_href_delay;
wire [7:0] cmos_data_delay;
camera_delay camera_delay_inst
(
   .cmos_pclk          (cmos_pclk),              //cmos pxiel clock
   .cmos_href          (cmos_href),              //cmos hsync refrence
   .cmos_vsync         (cmos_vsync),             //cmos vsync
   .cmos_data          (cmos_db),              //cmos data

   .cmos_href_delay    (cmos_href_delay),              //cmos hsync refrence
   .cmos_vsync_delay   (cmos_vsync_delay),             //cmos vsync
   .cmos_data_delay    (cmos_data_delay)             //cmos data
) ;
//////////////////// CMOS FIFO/////////////////// 
wire [11 : 0] fifo_data_count;
wire [7:0] fifo_data;
wire fifo_rd_en;
reg fifo_rd_en_reg;
camera_fifo camera_fifo_inst(       // 这个是写缓存
    .wr_clk(cmos_pclk),
    .wr_rst(cmos_vsync),
    .wr_en(cmos_href_delay),
    .wr_data(cmos_data_delay),
    .wr_full(),
    .wr_water_level(),
    .almost_full(),
    .rd_clk(HCLK),
    .rd_rst(cmos_vsync),
    .rd_en(fifo_rd_en),
    .rd_data(fifo_data),
    .rd_empty(),
    .rd_water_level(fifo_data_count),
    .almost_empty());


//CLK----------------------------------------------------------------
    // sysclk source
	`ifdef UNCACHE
	PLL u_PLL (
        .clkin1               (ex_clk_50m), // input
        .pll_lock             (pll_lock),   // output
        .clkout0              (HCLK),       // output
        .clkout1              ()            // output
    );
	`else
		assign HCLK = aclk_mux;
	`endif    

//Soft Reset---------------------------------------------------------  
    wire   DBGRESETn;
    wire   SYSRESETREQ;
    wire   SYSRESETn;

    rst_gen u_rst_gen(
        .HCLK                 (HCLK),           // input
        .pad_nRST             (1'b1),       // input  
        .ddrc_init_done       (ddrc_init_done), // input
        .watchdog_reset       (watchdog_reset), // input
        .SYSRESETREQ          (SYSRESETREQ),    // input
    
        .DBGRESETn            (DBGRESETn),      // output
        .SYSRESETn            (SYSRESETn)       // output
    );

//M1 CORE------------------------------------------------------------ 
    assign LED[1:0]    = p0_outen[1:0]  & p0_out[1:0];
    assign LED[2]      = ddrc_init_done;
    //assign LED[2]      = init_done;
    assign LED[3]      = heart_beat_led;
    assign gpio_out = p0_outen[15:8] & p0_out[15:8];

    wire [7:0] spi0_cs_0;
    assign spi0_cs = spi0_cs_0[0];
    // assign spi1_cs = spi0_cs_0[1];

    wire spi_clk;
    assign spi0_clk = spi_clk;
    // assign spi1_clk = spi_clk;
    wire spi_mosi;
    assign spi0_mosi = spi_mosi;
    // assign spi1_mosi = spi_mosi;
    wire spi_miso;
    assign spi_miso = (~spi0_cs_0[0])?spi0_miso:1'bz;
    // assign spi_miso = (~spi0_cs_0[0])?spi0_miso:(~spi0_cs_0[1])?spi1_miso:1'bz;

    wire scl_pad_i;
    wire scl_pad_o;
    wire sda_pad_i;
    wire sda_pad_o;

    assign i2c0_sck  = scl_pad_o ? 1'bz : 1'b0;
    assign i2c0_sda  = sda_pad_o ? 1'bz : 1'b0;
    assign scl_pad_i = i2c0_sck;
    assign sda_pad_i = i2c0_sda;

    assign m1_tpnd = tsmac_tpnd && ~udp_cs;

    //M1 core
    integration_kit_dbg u_integration_kit_dbg(   
		 // Inputs
        .HCLK              (HCLK),           // System Clock
        .SYSRESETn         (SYSRESETn),      // System Reset
        .DBGRESETn         (DBGRESETn),      // Debug Reset
      
        .nTRST             (pad_nTRST),      // JTAG reset
        .SWCLKTCK          (pad_TCK),        // Serial wire and JTAG clock
        .SWDITMS           (pad_TMS),        // SW Data / JTAG Test Mode Select
        .TDI               (pad_TDI),        // JTAG data input
        
        .EDBGRQ            (1'b0),           // Debug request
        .DBGRESTART        (1'b0),           // Restart from halt request

        .SYSRESETREQ       (SYSRESETREQ),    // Cortex-M1 SYSRESET request
        .LOCKUP            (),               // Cortex-M1 lockup
        .HALTED            (),               // Cortex-M1 halted
        .DBGRESTARTED      (),               // Restart from halt acknowledge
        
        .JTAGNSW           (),               // JTAG = 1, serial wire = 0
        .JTAGTOP           (),               // state controller indicator
        .TDO               (pad_TDO),        // JTAG data output
        .nTDOEN            (),               // JTAG data out enable
        .SWDO              (),               // Serial wire data out
        .SWDOEN            (),               // Serial data output enable

        //AHB AHB[31:28] = 4'h7,4'h8,4'h9    AHB[27:0] = 28'h000_0000 ~ 28'hfff_ffff
        .HSEL              (HSEL),           // AHB Memory select
        .HTRANS            (HTRANS),         // AHB Memory transaction type
        .HBURST            (HBURST),         // AHB Memory burst information
        .HPROT             (HPROT),          // AHB Memory protection control
        .HSIZE             (HSIZE),          // AHB Memory transfer size
        .HWRITE            (HWRITE),         // AHB Memory transfer direction
        .HMASTLOCK         (HMASTLOCK),      // AHB Memory locked transfer
        .HADDR             (HADDR),          // AHB Memory transfer address
        .HWDATA            (HWDATA),         // AHB Memory write data bus
        .HREADY            (HREADY),         // AHB Memory bus ready
        .HREADYOUT         (HREADYOUT_udp),  // AHB Memory ready
        .HRESP             (HRESP_udp),      // AHB Memory response
        .HRDATA            (HRDATA_udp),     // AHB Memory read data bus  
        .HRDATAmux         (HRDATAmux),

        //APB AHB[11:0]    AHB[31:0] = 32'h5000c000 ~ 32'h5000cfff
        .PADDR             (PADDR),   
        .PWRITE            (PWRITE),    
        .PWDATA            (PWDATA),    
        .PENABLE           (PENABLE),   
        .PSEL              (PSEL),      
        .PRDATA            (PRDATA),   
        .PREADY            (1'b1),  
        .PSLVERR           (1'b0),   

        //Periphral
        //GPIO
        .p0_out            (p0_out),         // GPIO 0 outputs
        .p0_outen          (p0_outen),       // GPIO 0 output enables
        .p0_altfunc        (),               // GPIO 0 alternate function (pin mux)
        .p0_in             ({{14{1'b0}}, gpio_in1, gpio_in0}),          // GPIO 0 inputs

        //UART0
        .RX0               (RX),
        .TX0               (TX),

        //UART1
        .RX1               (),
        .TX1               (),

        //WATCHDOG
        .watchdog_reset    (watchdog_reset),

        //SPI
        .spi0_clk          (spi_clk),
        .spi0_cs           (spi0_cs_0),
        .spi0_mosi         (spi_mosi),
        .spi0_miso         (spi_miso),

        //I2C 
        .scl_pad_i         (scl_pad_i),
        .scl_pad_o         (scl_pad_o),
        .sda_pad_i         (sda_pad_i),
        .sda_pad_o         (sda_pad_o),

        //MEM        
        .wdata             (wdata),
        .waddr             (waddr),
        .w_en              (w_en),
        .rdata             (rdata),
        .raddr             (raddr),
        .r_en              (r_en),
        .mem_cs            (mem_cs),

        //TSMAC
        .tsmac_tdata       (m1_tdata),
        .tsmac_tstart      (m1_tstart),
        .tsmac_tpnd        (m1_tpnd),
        .tsmac_tlast       (m1_tlast),

        .tsmac_rdata       (ethernet_fifo_rd_data[7:0]),
        .tsmac_rvalid      (ethernet_fifo_rd_data[8]),
        .tsmac_rlast       (ethernet_fifo_rd_data[9]),

        //DDR    
        .aclk_mux          (HCLK),              
        .awaddr_mux        (awaddr_mux),      
        .awlen_mux         (awlen_mux),            
        .awvalid_mux       (awvalid_mux),     
        .awready_mux       (awready_mux),        
        .wdata_mux         (wdata_mux),       
        .wstrb_mux         (wstrb_mux),       
        .wlast_mux         (wlast_mux),       
        .wvalid_mux        (wvalid_mux),      
        .wready_mux        (wready_mux),      
       
        .araddr_mux        (araddr_mux),      
        .arlen_mux         (arlen_mux),           
        .arvalid_mux       (arvalid_mux),     
        .arready_mux       (arready_mux),            
        .rdata_mux         (rdata_mux),            
        .rlast_mux         (rlast_mux),       
        .rvalid_mux        (rvalid_mux),      
        .rready_mux        (rready_mux)      
    );   

//UDP_HW_SPEEDUP--------------------------------------------------------
    wire HSEL_temp;
    assign HSEL_temp = HSEL && (HADDR[31:28] == 4'h7);

    assign test_datai = 'd0;
    assign test_dbusy = 'd0;
    assign udp_tpnd = tsmac_tpnd && udp_cs;

    // UDP SPEEDUP is driven from the AHB 
    // 关闭UDP 加速模块
    generate if (`CORTEXM1_AHB_UDP == 1) begin : gen_udp_hw_speedup_0
    udp_hw_speedup u_udp_hw_speedup(
        .HCLK                   (HCLK),         // system bus clock
        .HRESETn                (SYSRESETn),    // system bus reset
                                      
        .datai                  (test_datai),   // source data
        .dbusy                  (test_dbusy),   // source data valid  
        .dready                 (dready),       // hw_speedup_ready
                                                                                            
        .HSEL                   (HSEL_temp),    // AHB peripheral select
        .HREADY                 (HREADY),       // AHB ready input
        .HTRANS                 (HTRANS),       // AHB transfer type
        .HSIZE                  (HSIZE),        // AHB hsize
        .HWRITE                 (HWRITE),       // AHB hwrite
        .HADDR                  (HADDR),        // AHB address bus
        .HWDATA                 (HWDATA),       // AHB write data bus  
                         
        .HREADYOUT              (HREADYOUT_udp),// AHB ready output to S->M mux
        .HRESP                  (HRESP_udp),    // AHB response
        .HRDATA                 (HRDATA_udp),
    
        .udp_tdata              (udp_tdata),    // TSMAC tx data
        .udp_tstart             (udp_tstart),   // TSMAC tx start
        .udp_tpnd               (udp_tpnd),     // TSMAC tx going
        .udp_tlast              (udp_tlast),    // TSMAC tx end

        .udp_cs                 (udp_cs)        // UDP tx valid
    );
    end else
    begin : gen_no_udp_hw_speedup_0
      assign dready               = 1'b0;
    
      assign HREADYOUT_udp        = 1'b1;
      assign HRESP_udp            = 1'b0;
      assign HRDATA_udp           = {32{1'b0}};
    
      assign udp_tdata            = {8{1'b0}};
      assign udp_tstart           = 1'b0;
      assign udp_tlast            = 1'b0;
    
      assign udp_cs               = 1'b0;
    end endgenerate
    
//SD Card--------------------------------------------------------------
  wire [31:0] rdata1;
    wire a_wr_en;
    sd_card_top u_SD_CARD(
        .HCLK            (HCLK),
        .cs              (mem_cs[1]),
        .rst             (SYSRESETn),
        .wr_en           (w_en),
        .wr_data         (wdata),
        .waddr           (waddr),

        .rd_addr         (raddr),
        .rd_en           (r_en),
        .rd_data         (rdata1),
        .SD_nCS          (SD_nCS),
        .SD_DCLK         (SD_DCLK),
        .SD_MOSI         (SD_MOSI),
        .SD_MISO         (SD_MISO)
    );
//MEM-------------------------------------------------------------------

    assign a_wr_en = w_en | ~r_en;

    wire [31:0] rdata0;
    assign rdata = mem_cs[0]?rdata0:(mem_cs[1]?rdata1:(mem_cs[3]?rdata3:'d0));

    TEST_RAM u_TEST_RAM (
      .wr_data                  (wdata),        // input  [31:0]
      .wr_addr                  (waddr[7:0]),   // input  [7:0]
      .wr_en                    (a_wr_en),      // input
      .wr_clk                   (HCLK),         // input
      .wr_clk_en                (mem_cs[0]),    // input
      .wr_rst                   (1'b0),         // input

      .rd_addr                  (raddr[7:0]),   // input  [7:0]
      .rd_data                  (rdata0),       // output [31:0]
      .rd_clk                   (HCLK),         // input
      .rd_rst                   (1'b0)          // input
    );

//DDR------------------------------------------------------------------
    always@(posedge HCLK or negedge rst_key)
    begin
       if (!rst_key)
          cnt <= 27'd0;
       else if ( cnt >= TH_1S )
          cnt <= 27'd0;
       else
          cnt <= cnt + 27'd1;
    end
    
    always @(posedge HCLK or negedge rst_key)
    begin
       if (!rst_key)
          heart_beat_led <= 1'd1;
       else if ( cnt >= TH_1S )
          heart_beat_led <= ~heart_beat_led;
    end

    DDR3 u_DDR3 (
      .pll_refclk_in          (ex_clk_50m),     // input
      .top_rst_n              (rst_key),        // input
      .ddrc_rst               (1'b0),           // input
      .csysreq_ddrc           (1'b1),           // input
      .csysack_ddrc           (),               // output
      .cactive_ddrc           (),               // output
      .pll_lock               (ddrc_pll_lock),  // output
      .pll_aclk_0             (aclk_mux),       // output
      .pll_aclk_1             (aclk_1),         // output
      .pll_aclk_2             (),               // output
      .ddrphy_rst_done        (ddrphy_rst_done),// output
      .ddrc_init_done         (ddrc_init_done), // output

      .pad_loop_in            (pad_loop_in),    // input
      .pad_loop_in_h          (pad_loop_in_h),  // input
      .pad_rstn_ch0           (pad_rstn_ch0),   // output
      .pad_ddr_clk_w          (pad_ddr_clk_w),  // output
      .pad_ddr_clkn_w         (pad_ddr_clkn_w), // output
      .pad_csn_ch0            (pad_csn_ch0),    // output
      .pad_addr_ch0           (pad_addr_ch0),   // output [15:0]
      .pad_dq_ch0             (pad_dq_ch0),     // inout [15:0]
      .pad_dqs_ch0            (pad_dqs_ch0),    // inout [1:0]
      .pad_dqsn_ch0           (pad_dqsn_ch0),   // inout [1:0]
      .pad_dm_rdqs_ch0        (pad_dm_rdqs_ch0),// output [1:0]
      .pad_cke_ch0            (pad_cke_ch0),    // output
      .pad_odt_ch0            (pad_odt_ch0),    // output
      .pad_rasn_ch0           (pad_rasn_ch0),   // output
      .pad_casn_ch0           (pad_casn_ch0),   // output
      .pad_wen_ch0            (pad_wen_ch0),    // output
      .pad_ba_ch0             (pad_ba_ch0),     // output [2:0]
      .pad_loop_out           (pad_loop_out),   // output
      .pad_loop_out_h         (pad_loop_out_h), // output
        
      .areset_0               (1'b0),           // input
      .aclk_0                 (HCLK),           // input
      .awid_0                 (8'h00),          // input [7:0]
      .awaddr_0               (awaddr_mux),     // input [31:0]
      .awlen_0                (awlen_mux),      // input [7:0]
      .awsize_0               (3'b100),         // input [2:0]
      .awburst_0              (2'b01),          // input [1:0]
      .awlock_0               (1'b0),           // input
      .awvalid_0              (awvalid_mux),    // input
      .awready_0              (awready_mux),    // output
      .awurgent_0             (1'b0),           // input
      .awpoison_0             (1'b0),           // input
      .wdata_0                (wdata_mux),      // input [127:0]
      .wstrb_0                (wstrb_mux),      // input [15:0]
      .wlast_0                (wlast_mux),      // input
      .wvalid_0               (wvalid_mux),     // input
      .wready_0               (wready_mux),     // output
      .bid_0                  (),               // output [7:0]
      .bresp_0                (),               // output [1:0]
      .bvalid_0               (),               // output
      .bready_0               (1'b1),           // input

      .arid_0                 (8'h00),          // input [7:0]
      .araddr_0               (araddr_mux),     // input [31:0]
      .arlen_0                (arlen_mux),      // input [7:0]
      .arsize_0               (3'b100),         // input [2:0]
      .arburst_0              (2'b01),          // input [1:0]
      .arlock_0               (1'b0),           // input
      .arvalid_0              (arvalid_mux),    // input
      .arready_0              (arready_mux),    // output
      .arpoison_0             (1'b0),           // input
      .rid_0                  (),               // output [7:0]
      .rdata_0                (rdata_mux),      // output [127:0]
      .rresp_0                (),               // output [1:0]
      .rlast_0                (rlast_mux),      // output
      .rvalid_0               (rvalid_mux),     // output
      .rready_0               (rready_mux),     // input
      .arurgent_0             (1'b0),           // input
      .csysreq_0              (1'b1),           // input
      .csysack_0              (),               // output
      .cactive_0              (),               // output

       .areset_1               (1'b0),           // input
       .aclk_1                 (aclk_1),         // input
       .awid_1                 (8'h00),          // input [7:0]
       .awaddr_1               (awaddr_1),       // input [31:0]
       .awlen_1                (8'hff),          // input [7:0]
       .awsize_1               (3'b011),         // input [2:0]
       .awburst_1              (2'b01),          // input [1:0]
       .awlock_1               (1'b0),           // input
       .awvalid_1              (awvalid_1),      // input
       .awready_1              (awready_1),      // output
       .awurgent_1             (1'b0),           // input
       .awpoison_1             (1'b0),           // input
       .wdata_1                (wdata_1),        // input [63:0]
       .wstrb_1                (8'hff),          // input [7:0]
       .wlast_1                (wlast_1),        // input
       .wvalid_1               (wvalid_1),       // input
       .wready_1               (wready_1),       // output
       .bid_1                  (),               // output [7:0]
       .bresp_1                (),               // output [1:0]
       .bvalid_1               (),               // output
       .bready_1               (1'b1),           // input

       .arid_1                 (8'h00),          // input [7:0]
       .araddr_1               (araddr_1),       // input [31:0]
       .arlen_1                (8'hff),          // input [7:0]
       .arsize_1               (3'b011),         // input [2:0]
       .arburst_1              (2'b01),          // input [1:0]
       .arlock_1               (1'b0),           // input
       .arvalid_1              (arvalid_1),      // input
       .arready_1              (arready_1),      // output
       .arpoison_1             (1'b0),           // input
       .rid_1                  (),               // output [7:0]
       .rdata_1                (rdata_1),        // output [63:0]
       .rresp_1                (),               // output [1:0]
       .rlast_1                (rlast_1),        // output
       .rvalid_1               (rvalid_1),       // output
       .rready_1               (rready_1),       // input
       .arurgent_1             (1'b0),           // input
       .csysreq_1              (1'b1),           // input
       .csysack_1              (),               // output
       .cactive_1              ()                // output
    );

    // 
    wire [31:0] rdata3;
    cam_ddr_ahb_contorl cam_ddr_ahb_contorl_i0(
                                                // 这个时钟是AXI接口的时钟，好像是100M
                                                
        /*              cmos signals        */
        .fifo_data_count(fifo_data_count),       // input [11:0]
        .fifo_data(fifo_data),           // input [7:0]
        .fifo_rd_en(fifo_rd_en),         // output
        .cmos_init_done(init_done), //input

        /*------------ ahb interface ---------------*/
        .HCLK            (HCLK),                // 这个时钟是AHB总线的读写时钟，频率不知道
        .cs              (mem_cs[3]),
        .rst             (SYSRESETn),
        .wr_en           (w_en),
        .wr_data         (wdata),
        .waddr           (waddr),

        .rd_addr         (raddr),
        .rd_en           (r_en),
        .rd_data         (rdata3),

      //AXI WRITE                               
      .aclk                   (aclk_1),         // input 100Mhz 
      .awaddr_1               (awaddr_1),       // output
      .awvalid_1              (awvalid_1),      // output
      .awready_1              (awready_1),      // input
      .wdata_1                (wdata_1),        // output
      .wlast_1                (wlast_1),        // output
      .wvalid_1               (wvalid_1),       // output
      .wready_1               (wready_1),       // input
                                                
      //AXI READ                                
      // 读端口在这个版本用不上，不需要从这里读，软核通过Dcache读
      .araddr_1               (araddr_1),       // output
      .arvalid_1              (arvalid_1),      // output
      .arready_1              (arready_1),      // input
      .rdata_1                (rdata_1),        // input
      .rlast_1                (rlast_1),        // input
      .rvalid_1               (rvalid_1),       // input
      .rready_1               (rready_1)        // output
    );

//TSMAC-------------------------------------------------------------------------------------------------  
    assign {phy_txd3,phy_txd2,phy_txd1,phy_txd0} = phy_txd;
    assign phy_rxd = {phy_rxd3,phy_rxd2,phy_rxd1,phy_rxd0};
    // assign phy_rst_n = rst_key;

    assign tsmac_phy_mdi  = tsmac_phy_mdio;
    assign tsmac_phy_mdio = tsmac_phy_mdoen ? tsmac_phy_mdo : 1'bz;

    assign tsmac_fifo_wr_data = {10{tsmac_rvalid}} & {tsmac_rlast,tsmac_rvalid,tsmac_rdata};

    //tx_clk
    wire pado;
    wire padt;
    
    GTP_OSERDES #(
     .OSERDES_MODE            ("ODDR"),         //"ODDR","OMDDR","OGSER4","OMSER4","OGSER7","OGSER8",OMSER8"
     .WL_EXTEND               ("FALSE"),        //"TRUE"; "FALSE"
     .GRS_EN                  ("TRUE"),         //"TRUE"; "FALSE"
     .LRS_EN                  ("TRUE"),         //"TRUE"; "FALSE"
     .TSDDR_INIT              (1'b0)            //1'b0;1'b1
    ) u_GTP_OGDDR(
       .DO                    (pado),
       .TQ                    (padt),
       .DI                    (8'b00000001),
       .TI                    (4'd0),
       .RCLK                  (HCLK),
       .SERCLK                (HCLK),
       .OCLK                  (1'd0),
       .RST                   (~SYSRESETn)
    ); 
    
    GTP_OUTBUFT u_GTP_OUTBUFT
    (
        .O                    (l0_sgmii_clk_shft),
        .I                    (pado),
        .T                    (padt)
    );
    
    //rx_clk
    wire rx_clki_shft_bufg;   
    GTP_IOCLKDELAY
    #(
        .DELAY_STEP_VALUE     (8'd70), 
        .SIM_DEVICE           ("LOGOS"),
        .DELAY_STEP_SEL       ("PARAMETER") //"PARAMETER"/ "PORT"    ,pgh "PARAMETER"-->1'b1-->delay_step_value    pgl  "PARAMETER"-->1'b0-->delay_step_value
    )u_GTP_IOCLKDELAY(        
        .CLKOUT               (rx_clki_shft_bufg),
        .DELAY_OB             (),
        .CLKIN                (rx_clki),
        .DELAY_STEP           (),
        .DIRECTION            (1'b1),
        .LOAD                 (1'b1),
        .MOVE                 (1'b0)
    );      

    wire rx_clki_clkbufg;
    GTP_CLKBUFG u_GTP_CLKBUFG
    (
        .CLKOUT               (rx_clki_clkbufg),
        .CLKIN                (rx_clki_shft_bufg)
    );

    TSMAC_FIFO_RXCKLI u_TSMAC_FIFO_RXCKLI (
      .wr_clk                 (rx_clki_clkbufg),       // input
      .wr_rst                 (~SYSRESETn),            // input
      .wr_en                  (1'b1),                  // input
      .wr_data                (tsmac_fifo_wr_data),    // input [9:0]
      .wr_full                (),                      // output
      .almost_full            (),                      // output
      .rd_clk                 (HCLK),                  // input
      .rd_rst                 (~SYSRESETn),            // input
      .rd_en                  (1'b1),                  // input
      .rd_data                (ethernet_fifo_rd_data), // output [9:0]
      .rd_empty               (),      		           // output
      .almost_empty           ()                       // output
    );

    wire PSEL_temp;
    wire PENABLE_temp;
    assign PSEL_temp    = PSEL && (PADDR < 12'h300);
    assign PENABLE_temp = PENABLE && (PADDR < 12'h300);
    
    assign tsmac_tdata  = udp_cs ? udp_tdata  : m1_tdata;
    assign tsmac_tstart = udp_cs ? udp_tstart : m1_tstart;
    assign tsmac_tlast  = udp_cs ? udp_tlast  : m1_tlast;

    //tsmac
    tsmac_phy   u_tsmac_phy(
        .tx_clki              (HCLK),
        .rx_clki              (rx_clki_clkbufg),
        .tx_rst               (~SYSRESETn),
        .rx_rst               (~SYSRESETn),
                              
        .mdi                  (tsmac_phy_mdi),
        .mdc                  (tsmac_phy_mdc),
        .mdo                  (tsmac_phy_mdo),
        .mdoen                (tsmac_phy_mdoen),
                              
        .tsmac_tcrq           (1'b0),
        .tsmac_cfpt           (16'h0000),
        .tsmac_thdf           (1'b0),
        .tsmac_tprt           (),
        .tsmac_tpar           (),
        .tsmac_txcf           (),
        .tsmac_tcdr           (),
                              
        .rx_dv                (phy_rx_dv),
        .rxd                  (phy_rxd  ),
        .tx_en                (phy_tx_en),
        .txd                  (phy_txd  ),
                              
        .presetn              (~SYSRESETn),
        .pclk                 (HCLK),
        .pselx                (PSEL_temp),
        .pwrite               (PWRITE),
        .penable              (PENABLE_temp),
        .paddr                (PADDR[11:4]),
        .pwdata               (PWDATA),
        .prdata               (),  

        .tsmac_tsvp           (),
        .tsmac_tsv            (),
        .tsmac_rsvp           (),
        .tsmac_rsv            (),
                              
        .tsmac_tpnd           (tsmac_tpnd  ),
        .tsmac_tdata          (tsmac_tdata ),
        .tsmac_tstart         (tsmac_tstart),
        .tsmac_tlast          (tsmac_tlast ),
                              
        .tsmac_rdata          (tsmac_rdata),
        .tsmac_rvalid         (tsmac_rvalid),
        .tsmac_rlast          (tsmac_rlast),
                              
        .speed                ()
    );

endmodule