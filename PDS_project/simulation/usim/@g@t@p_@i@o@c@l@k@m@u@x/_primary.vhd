library verilog;
use verilog.vl_types.all;
entity GTP_IOCLKMUX is
    port(
        CLKOUT          : out    vl_logic;
        CLKIN0          : in     vl_logic;
        CLKIN1          : in     vl_logic;
        SEL             : in     vl_logic
    );
end GTP_IOCLKMUX;
