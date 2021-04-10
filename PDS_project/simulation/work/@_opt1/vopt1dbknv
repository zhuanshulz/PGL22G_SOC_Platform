library verilog;
use verilog.vl_types.all;
entity ipml_fifo_v1_5_TSMAC_FIFO_RXCKLI is
    generic(
        c_SIM_DEVICE    : string  := "LOGOS";
        c_WR_DEPTH_WIDTH: integer := 10;
        c_WR_DATA_WIDTH : integer := 32;
        c_RD_DEPTH_WIDTH: integer := 10;
        c_RD_DATA_WIDTH : integer := 32;
        c_OUTPUT_REG    : integer := 0;
        c_RD_OCE_EN     : integer := 0;
        c_RESET_TYPE    : string  := "ASYNC_RESET";
        c_POWER_OPT     : integer := 0;
        c_RD_CLK_OR_POL_INV: integer := 0;
        c_WR_BYTE_EN    : integer := 0;
        c_BE_WIDTH      : integer := 8;
        c_FIFO_TYPE     : string  := "SYN";
        c_ALMOST_FULL_NUM: integer := 508;
        c_ALMOST_EMPTY_NUM: integer := 4
    );
    port(
        wr_data         : in     vl_logic_vector;
        wr_en           : in     vl_logic;
        wr_clk          : in     vl_logic;
        wr_full         : out    vl_logic;
        wr_rst          : in     vl_logic;
        wr_byte_en      : in     vl_logic_vector;
        almost_full     : out    vl_logic;
        wr_water_level  : out    vl_logic_vector;
        rd_data         : out    vl_logic_vector;
        rd_en           : in     vl_logic;
        rd_clk          : in     vl_logic;
        rd_empty        : out    vl_logic;
        rd_rst          : in     vl_logic;
        rd_oce          : in     vl_logic;
        almost_empty    : out    vl_logic;
        rd_water_level  : out    vl_logic_vector
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of c_SIM_DEVICE : constant is 1;
    attribute mti_svvh_generic_type of c_WR_DEPTH_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_WR_DATA_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_RD_DEPTH_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_RD_DATA_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_OUTPUT_REG : constant is 1;
    attribute mti_svvh_generic_type of c_RD_OCE_EN : constant is 1;
    attribute mti_svvh_generic_type of c_RESET_TYPE : constant is 1;
    attribute mti_svvh_generic_type of c_POWER_OPT : constant is 1;
    attribute mti_svvh_generic_type of c_RD_CLK_OR_POL_INV : constant is 1;
    attribute mti_svvh_generic_type of c_WR_BYTE_EN : constant is 1;
    attribute mti_svvh_generic_type of c_BE_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_FIFO_TYPE : constant is 1;
    attribute mti_svvh_generic_type of c_ALMOST_FULL_NUM : constant is 1;
    attribute mti_svvh_generic_type of c_ALMOST_EMPTY_NUM : constant is 1;
end ipml_fifo_v1_5_TSMAC_FIFO_RXCKLI;
