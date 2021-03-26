library verilog;
use verilog.vl_types.all;
entity V_OSC_E2 is
    generic(
        USER_DIV_EN     : string  := "TRUE";
        CLK_DIV         : integer := 0
    );
    port(
        EN_N            : in     vl_logic;
        CLKOUT          : out    vl_logic;
        CLKCRC          : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of USER_DIV_EN : constant is 1;
    attribute mti_svvh_generic_type of CLK_DIV : constant is 1;
end V_OSC_E2;
