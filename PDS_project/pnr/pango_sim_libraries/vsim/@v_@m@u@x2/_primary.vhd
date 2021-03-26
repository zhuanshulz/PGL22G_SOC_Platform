library verilog;
use verilog.vl_types.all;
entity V_MUX2 is
    port(
        Z               : out    vl_logic;
        I0              : in     vl_logic;
        I1              : in     vl_logic;
        SEL             : in     vl_logic
    );
end V_MUX2;
