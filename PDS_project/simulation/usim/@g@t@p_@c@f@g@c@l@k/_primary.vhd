library verilog;
use verilog.vl_types.all;
entity GTP_CFGCLK is
    port(
        CLKIN           : in     vl_logic;
        CE_N            : in     vl_logic
    );
end GTP_CFGCLK;
