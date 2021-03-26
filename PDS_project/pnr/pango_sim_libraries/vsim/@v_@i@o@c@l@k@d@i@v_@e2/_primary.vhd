library verilog;
use verilog.vl_types.all;
entity V_IOCLKDIV_E2 is
    generic(
        DIV_FACTOR      : string  := "BYPASS"
    );
    port(
        CLKDIVOUT       : out    vl_logic;
        CLKIN           : in     vl_logic;
        RST_N           : in     vl_logic;
        CE              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of DIV_FACTOR : constant is 1;
end V_IOCLKDIV_E2;
