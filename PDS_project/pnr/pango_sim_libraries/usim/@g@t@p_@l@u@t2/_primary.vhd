library verilog;
use verilog.vl_types.all;
entity GTP_LUT2 is
    generic(
        INIT            : vl_logic_vector(3 downto 0) := (Hi0, Hi0, Hi0, Hi0)
    );
    port(
        Z               : out    vl_logic;
        I0              : in     vl_logic;
        I1              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of INIT : constant is 2;
end GTP_LUT2;
