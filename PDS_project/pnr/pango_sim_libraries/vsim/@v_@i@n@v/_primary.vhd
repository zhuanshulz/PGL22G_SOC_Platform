library verilog;
use verilog.vl_types.all;
entity V_INV is
    port(
        Z               : out    vl_logic;
        I               : in     vl_logic
    );
end V_INV;
