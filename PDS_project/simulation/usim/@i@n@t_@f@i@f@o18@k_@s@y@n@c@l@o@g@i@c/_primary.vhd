library verilog;
use verilog.vl_types.all;
entity INT_FIFO18K_SYNCLOGIC is
    generic(
        ASIZE           : integer := 12;
        c_DW            : integer := 15
    );
    port(
        sync_fifo       : in     vl_logic;
        gray_en         : in     vl_logic;
        src_clk         : in     vl_logic;
        rstn_src        : in     vl_logic;
        src_data        : in     vl_logic_vector;
        des_clk         : in     vl_logic;
        rstn_des        : in     vl_logic;
        des_data        : out    vl_logic_vector
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of ASIZE : constant is 1;
    attribute mti_svvh_generic_type of c_DW : constant is 1;
end INT_FIFO18K_SYNCLOGIC;
