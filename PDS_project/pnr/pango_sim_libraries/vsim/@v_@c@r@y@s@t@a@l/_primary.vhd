library verilog;
use verilog.vl_types.all;
entity V_CRYSTAL is
    generic(
        CLK_EN          : string  := "FALSE"
    );
    port(
        CLKOUT          : out    vl_logic;
        XTALA           : in     vl_logic;
        XTALB           : in     vl_logic;
        EN_N            : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of CLK_EN : constant is 1;
end V_CRYSTAL;
