library verilog;
use verilog.vl_types.all;
entity ipml_fifo_ctrl_v1_3 is
    generic(
        c_WR_DEPTH_WIDTH: integer := 9;
        c_RD_DEPTH_WIDTH: integer := 9;
        c_FIFO_TYPE     : string  := "ASYN";
        c_ALMOST_FULL_NUM: integer := 508;
        c_ALMOST_EMPTY_NUM: integer := 4
    );
    port(
        wclk            : in     vl_logic;
        w_en            : in     vl_logic;
        waddr           : out    vl_logic_vector;
        wrst            : in     vl_logic;
        wfull           : out    vl_logic;
        almost_full     : out    vl_logic;
        wr_water_level  : out    vl_logic_vector;
        rclk            : in     vl_logic;
        r_en            : in     vl_logic;
        raddr           : out    vl_logic_vector;
        rrst            : in     vl_logic;
        rempty          : out    vl_logic;
        rd_water_level  : out    vl_logic_vector;
        almost_empty    : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of c_WR_DEPTH_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_RD_DEPTH_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of c_FIFO_TYPE : constant is 1;
    attribute mti_svvh_generic_type of c_ALMOST_FULL_NUM : constant is 1;
    attribute mti_svvh_generic_type of c_ALMOST_EMPTY_NUM : constant is 1;
end ipml_fifo_ctrl_v1_3;
