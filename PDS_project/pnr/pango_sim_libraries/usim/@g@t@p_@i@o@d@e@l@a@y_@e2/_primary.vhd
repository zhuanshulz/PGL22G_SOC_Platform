library verilog;
use verilog.vl_types.all;
entity GTP_IODELAY_E2 is
    generic(
        DELAY_STEP_SEL  : string  := "PARAMETER";
        DELAY_STEP_VALUE: vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        DO              : out    vl_logic;
        DI              : in     vl_logic;
        DELAY_SEL       : in     vl_logic;
        DELAY_STEP      : in     vl_logic_vector(7 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of DELAY_STEP_SEL : constant is 1;
    attribute mti_svvh_generic_type of DELAY_STEP_VALUE : constant is 2;
end GTP_IODELAY_E2;
