library verilog;
use verilog.vl_types.all;
entity GTP_MUX2LUT7 is
    port(
        Z               : out    vl_logic;
        I0              : in     vl_logic;
        I1              : in     vl_logic;
        S               : in     vl_logic
    );
end GTP_MUX2LUT7;
