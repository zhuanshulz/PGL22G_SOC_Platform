library verilog;
use verilog.vl_types.all;
entity V_ODDR_E1 is
    generic(
        ODDR_MODE       : string  := "SAME_EDGE";
        GRS_EN          : string  := "TRUE";
        RS_TYPE         : string  := "ASYNC_RESET"
    );
    port(
        Q               : out    vl_logic;
        D0              : in     vl_logic;
        D1              : in     vl_logic;
        CLK             : in     vl_logic;
        CE              : in     vl_logic;
        RS              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of ODDR_MODE : constant is 1;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of RS_TYPE : constant is 1;
end V_ODDR_E1;
