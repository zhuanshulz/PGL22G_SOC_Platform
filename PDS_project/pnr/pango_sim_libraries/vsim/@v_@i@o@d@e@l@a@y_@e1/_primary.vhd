library verilog;
use verilog.vl_types.all;
entity V_IODELAY_E1 is
    generic(
        DELAY_STEP_VALUE: vl_logic_vector(4 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0);
        DELAY_STEP_SEL  : string  := "PARAMETER"
    );
    port(
        DO              : out    vl_logic;
        DI              : in     vl_logic;
        DELAY_STEP      : in     vl_logic_vector(4 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of DELAY_STEP_VALUE : constant is 2;
    attribute mti_svvh_generic_type of DELAY_STEP_SEL : constant is 1;
end V_IODELAY_E1;
