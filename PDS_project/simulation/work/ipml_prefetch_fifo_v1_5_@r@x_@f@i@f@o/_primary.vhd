library verilog;
use verilog.vl_types.all;
entity ipml_prefetch_fifo_v1_5_RX_FIFO is
    generic(
        c_SIM_DEVICE    : string  := "LOGOS";
        c_WR_DEPTH_WIDTH: integer := 10;
        c_WR_DATA_WIDTH : integer := 32;
        c_RD_DEPTH_WIDTH: integer := 10;
        c_RD_DATA_WIDTH : integer := 32;
        c_RESET_TYPE    : string  := "ASYNC_RESET";
        c_POWER_OPT     : integer := 0;
        c_FIFO_TYPE     : string  := "SYN"
    );
    port(
        wr_data         : in     vl_logic_vector;
        wr_en           : in     vl_logic;
        wr_vld          : out    vl_logic;
        wr_clk          : in     vl_logic;
        wr_rst          : in     vl_logic;
        rd_data         : out    vl_logic_vector;
        rd_en           : in     vl_logic;
        rd_vld          : out    vl_logic;
        rd_clk          : in     vl_logic;
        rd_rst          : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of c_SIM_DEVICE : constant is 1;
    attribute mti_svvh_generic_type of c_WR_DEPTH_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_WR_DATA_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_RD_DEPTH_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_RD_DATA_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_RESET_TYPE : constant is 1;
    attribute mti_svvh_generic_type of c_POWER_OPT : constant is 1;
    attribute mti_svvh_generic_type of c_FIFO_TYPE : constant is 1;
end ipml_prefetch_fifo_v1_5_RX_FIFO;
