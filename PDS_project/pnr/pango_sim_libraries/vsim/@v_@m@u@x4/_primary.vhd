library verilog;
use verilog.vl_types.all;
entity V_MUX4 is
    port(
        Z               : out    vl_logic;
        S0              : in     vl_logic;
        S1              : in     vl_logic;
        I0              : in     vl_logic;
        I1              : in     vl_logic;
        I2              : in     vl_logic;
        I3              : in     vl_logic
    );
end V_MUX4;
