library verilog;
use verilog.vl_types.all;
entity apm_sign_extend is
    generic(
        width           : integer := 4
    );
    port(
        o               : out    vl_logic_vector;
        i               : in     vl_logic_vector;
        se              : in     vl_logic_vector
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of width : constant is 1;
end apm_sign_extend;
