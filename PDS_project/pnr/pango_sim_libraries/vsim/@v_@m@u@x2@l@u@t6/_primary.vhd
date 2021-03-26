library verilog;
use verilog.vl_types.all;
entity V_MUX2LUT6 is
    port(
        Z               : out    vl_logic;
        I0              : in     vl_logic;
        I1              : in     vl_logic;
        S               : in     vl_logic
    );
end V_MUX2LUT6;
