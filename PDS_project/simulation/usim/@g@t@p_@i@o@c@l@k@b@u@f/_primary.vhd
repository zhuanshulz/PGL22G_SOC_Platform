library verilog;
use verilog.vl_types.all;
entity GTP_IOCLKBUF is
    generic(
        GATE_EN         : string  := "FALSE"
    );
    port(
        CLKOUT          : out    vl_logic;
        CLKIN           : in     vl_logic;
        DI              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GATE_EN : constant is 1;
end GTP_IOCLKBUF;
