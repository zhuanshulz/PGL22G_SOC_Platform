library verilog;
use verilog.vl_types.all;
entity pgm_sdpram_v1_1 is
    generic(
        c_WR_ADDR_WIDTH : integer := 10;
        c_WR_DATA_WIDTH : integer := 32;
        c_RD_ADDR_WIDTH : integer := 10;
        c_RD_DATA_WIDTH : integer := 32;
        c_OUTPUT_REG    : integer := 0;
        c_RD_CLK_OR_POL_INV: integer := 0;
        c_RESET_TYPE    : string  := "ASYNC_RESET";
        c_POWER_OPT     : integer := 0;
        c_INIT_FILE     : string  := "NONE";
        c_INIT_FORMAT   : string  := "BIN";
        c_WR_BYTE_EN    : integer := 0;
        c_BE_WIDTH      : integer := 4
    );
    port(
        wr_data         : in     vl_logic_vector;
        wr_addr         : in     vl_logic_vector;
        wr_en           : in     vl_logic;
        wr_clk          : in     vl_logic;
        wr_clk_en       : in     vl_logic;
        wr_rst          : in     vl_logic;
        wr_byte_en      : in     vl_logic_vector;
        wr_addr_strobe  : in     vl_logic;
        rd_data         : out    vl_logic_vector;
        rd_addr         : in     vl_logic_vector;
        rd_clk          : in     vl_logic;
        rd_clk_en       : in     vl_logic;
        rd_rst          : in     vl_logic;
        rd_oce          : in     vl_logic;
        rd_addr_strobe  : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of c_WR_ADDR_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_WR_DATA_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_RD_ADDR_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_RD_DATA_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_OUTPUT_REG : constant is 1;
    attribute mti_svvh_generic_type of c_RD_CLK_OR_POL_INV : constant is 1;
    attribute mti_svvh_generic_type of c_RESET_TYPE : constant is 1;
    attribute mti_svvh_generic_type of c_POWER_OPT : constant is 1;
    attribute mti_svvh_generic_type of c_INIT_FILE : constant is 1;
    attribute mti_svvh_generic_type of c_INIT_FORMAT : constant is 1;
    attribute mti_svvh_generic_type of c_WR_BYTE_EN : constant is 1;
    attribute mti_svvh_generic_type of c_BE_WIDTH : constant is 1;
end pgm_sdpram_v1_1;
