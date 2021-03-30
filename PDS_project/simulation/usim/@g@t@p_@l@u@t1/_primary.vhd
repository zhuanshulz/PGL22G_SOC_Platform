library verilog;
use verilog.vl_types.all;
entity GTP_LUT1 is
    generic(
        INIT            : vl_logic_vector(1 downto 0) := (Hi0, Hi0)
    );
    port(
        Z               : out    vl_logic;
        I0              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of INIT : constant is 2;
end GTP_LUT1;
