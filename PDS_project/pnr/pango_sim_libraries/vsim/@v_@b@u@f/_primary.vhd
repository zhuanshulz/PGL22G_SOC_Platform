library verilog;
use verilog.vl_types.all;
entity V_BUF is
    port(
        Z               : out    vl_logic;
        I               : in     vl_logic
    );
end V_BUF;
