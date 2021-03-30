library verilog;
use verilog.vl_types.all;
entity GTP_CLKBUFM is
    port(
        CLKOUT          : out    vl_logic;
        CLKIN           : in     vl_logic
    );
end GTP_CLKBUFM;
