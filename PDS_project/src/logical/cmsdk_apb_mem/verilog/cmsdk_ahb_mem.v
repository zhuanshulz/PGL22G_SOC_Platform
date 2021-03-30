module cmsdk_ahb_mem(
// ----------------------------------------------------------------------------
// Port Definitions
// ----------------------------------------------------------------------------
   // AHB Inputs
   input  wire                 HCLK,      // system bus clock
   input  wire                 HRESETn,   // system bus reset
   input  wire                 FCLK,      // system bus clock
   input  wire                 HSEL,      // AHB peripheral select
   input  wire                 HREADY,    // AHB ready input
   input  wire  [1:0]          HTRANS,    // AHB transfer type
                                          // b00 IDLE. Indicates that no data transfer is required. A master uses an IDLE transfer when it does 
                                          //           not want to perform a data transfer. It is recommended that the master terminates a locked 
                                          //           transfer with an IDLE transfer.
                                          //           Slaves must always provide a zero wait state OKAY response to IDLE transfers and the 
                                          //           transfer must be ignored by the slave.
                                          // b01 BUSY. The BUSY transfer type enables masters to insert idle cycles in the middle of a burst.
                                          //            Slaves must always provide a zero wait state OKAY response to BUSY transfers and the 
                                          //            transfer must be ignored by the slave.
                                          // b10 NON SEQ. Indicates a single transfer or the first transfer of a burst.
                                          //              The address and control signals are unrelated to the previous transfer.
                                          //              Single transfers on the bus are treated as bursts of length one and
                                          //              therefore the transfer type is NONSEQUENTIAL.
                                          // b11 SEQ. The remaining transfers in a burst are SEQUENTIAL and the address  
                                          //          is related to the previous transfer.
                                          //          The control information is identical to the previous transfer.
                                          //          The address is equal to the address of the previous transfer plus the transfer size, in bytes, 
                                          //          with the transfer size being signaled by the HSIZE[2:0] signals. In the case of a wrapping 
                                          //          burst the address of the transfer wraps at the address boundary.
                                          //          
   input  wire  [2:0]          HSIZE,     // AHB hsize. indicates the size of a data transfer. 
                                          // The transfer size set by HSIZE must be less than or equal to the width of the data bus. 
                                          // HSIZE[2] HSIZE[1] HSIZE[0] Size (bits) Description
                                          //   0        0         0         8         Byte
                                          //   0        0         1         16      Halfword
                                          //   0        1         0         32        Word
                                          //   0        1         1         64      Doubleword
                                          //   1        0         0         128     4-word line
                                          //   1        0         1         256     8-word line
                                          //   1        1         0         512         -
                                          //   1        1         1         1024        -
   input  wire                 HWRITE,    // AHB hwrite
   input  wire [31:0]          HADDR,     // AHB address bus
   input  wire [31:0]          HWDATA,    // AHB write data bus

   input  wire  [3:0]          ECOREVNUM,  // Engineering-change-order revision bits

   // AHB Outputs
   output wire                 HREADYOUT, // AHB ready output to S->M mux
   output wire                 HRESP,     // AHB response
                                      //                                 HREADY
                                      // HRESP             0                                  1
                                      //   0       Transfer pending              Successful transfer completed
                                      //   1     ERROR response, first cycle       ERROR response, second cycle
   output wire [31:0]          HRDATA,

   output wire  [31:0]         wdata,
   output wire  [21:0]         waddr,
   output wire                 w_en,
   input  wire  [31:0]         rdata,
   output wire  [21:0]         raddr,
   output wire                 r_en,
   output wire  [15:0]         mem_cs);   // Combined interrupt

  //write data
   wire data_valid;
   assign data_valid = HSEL & HREADY & HTRANS[1];

   wire   w_data_en;
   assign w_data_en = data_valid & HWRITE;

   wire   r_data_en;
   assign r_data_en = data_valid & ~HWRITE;

   reg  w_data_en_t;

   always @ (posedge HCLK or negedge HRESETn) begin
     if(!HRESETn) w_data_en_t <= 1'b0;
     else w_data_en_t <= w_data_en;     
   end

   reg [31:0] addr;
   always @ (posedge HCLK or negedge HRESETn) begin
     if(!HRESETn) addr <= 32'h0;
     else addr <= HADDR;     
   end



   assign wdata = HWDATA;
   assign waddr = addr[23:2];
   assign w_en  = w_data_en_t;

   assign HRDATA = rdata;
   assign raddr  = HADDR[23:2];
   assign r_en   = r_data_en;

   assign mem_cs[0]  = ((addr[27:24] == 4'h0 && w_data_en_t) || (HADDR[27:24] == 4'h0 && r_data_en));  //reserved
   assign mem_cs[1]  = ((addr[27:24] == 4'h1 && w_data_en_t) || (HADDR[27:24] == 4'h1 && r_data_en));  
   assign mem_cs[2]  = ((addr[27:24] == 4'h2 && w_data_en_t) || (HADDR[27:24] == 4'h2 && r_data_en));  
   assign mem_cs[3]  = ((addr[27:24] == 4'h3 && w_data_en_t) || (HADDR[27:24] == 4'h3 && r_data_en));  
   assign mem_cs[4]  = ((addr[27:24] == 4'h4 && w_data_en_t) || (HADDR[27:24] == 4'h4 && r_data_en));  
   assign mem_cs[5]  = ((addr[27:24] == 4'h5 && w_data_en_t) || (HADDR[27:24] == 4'h5 && r_data_en));  
   assign mem_cs[6]  = ((addr[27:24] == 4'h6 && w_data_en_t) || (HADDR[27:24] == 4'h6 && r_data_en));  
   assign mem_cs[7]  = ((addr[27:24] == 4'h7 && w_data_en_t) || (HADDR[27:24] == 4'h7 && r_data_en));  
   assign mem_cs[8]  = ((addr[27:24] == 4'h8 && w_data_en_t) || (HADDR[27:24] == 4'h8 && r_data_en));  
   assign mem_cs[9]  = ((addr[27:24] == 4'h9 && w_data_en_t) || (HADDR[27:24] == 4'h9 && r_data_en));  
   assign mem_cs[10] = ((addr[27:24] == 4'ha && w_data_en_t) || (HADDR[27:24] == 4'ha && r_data_en));   
   assign mem_cs[11] = ((addr[27:24] == 4'hb && w_data_en_t) || (HADDR[27:24] == 4'hb && r_data_en));  
   assign mem_cs[12] = ((addr[27:24] == 4'hc && w_data_en_t) || (HADDR[27:24] == 4'hc && r_data_en));  
   assign mem_cs[13] = ((addr[27:24] == 4'hd && w_data_en_t) || (HADDR[27:24] == 4'hd && r_data_en));  
   assign mem_cs[14] = ((addr[27:24] == 4'he && w_data_en_t) || (HADDR[27:24] == 4'he && r_data_en));  
   assign mem_cs[15] = ((addr[27:24] == 4'hf && w_data_en_t) || (HADDR[27:24] == 4'hf && r_data_en));  

   assign HREADYOUT = 1'b1;
   assign HRESP     = 1'b0;


endmodule