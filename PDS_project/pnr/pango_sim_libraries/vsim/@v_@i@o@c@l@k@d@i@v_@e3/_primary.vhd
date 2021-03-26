library verilog;
use verilog.vl_types.all;
entity V_IOCLKDIV_E3 is
    generic(
        DIV_FACTOR      : string  := "8";
        PHASE_SHIFT     : string  := "0"
    );
    port(
        RST             : in     vl_logic;
        CLKIN           : in     vl_logic;
        CLKDIVOUT       : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of DIV_FACTOR : constant is 1;
    attribute mti_svvh_generic_type of PHASE_SHIFT : constant is 1;
end V_IOCLKDIV_E3;
