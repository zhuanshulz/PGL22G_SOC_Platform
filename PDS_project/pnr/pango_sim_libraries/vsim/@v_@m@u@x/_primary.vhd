library verilog;
use verilog.vl_types.all;
entity V_MUX is
    generic(
        SEL             : string  := "I0"
    );
    port(
        Y               : out    vl_logic;
        I0              : in     vl_logic;
        I1              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of SEL : constant is 1;
end V_MUX;
