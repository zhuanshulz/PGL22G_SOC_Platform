library verilog;
use verilog.vl_types.all;
entity GTP_OSC_E4 is
    port(
        CLKOUT          : out    vl_logic;
        EN_N            : in     vl_logic
    );
end GTP_OSC_E4;
