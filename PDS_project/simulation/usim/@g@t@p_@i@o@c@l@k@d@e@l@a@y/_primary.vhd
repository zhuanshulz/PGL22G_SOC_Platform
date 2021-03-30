library verilog;
use verilog.vl_types.all;
entity GTP_IOCLKDELAY is
    generic(
        DELAY_STEP_VALUE: vl_logic_vector(0 to 7) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        SIM_DEVICE      : string  := "TITAN";
        DELAY_STEP_SEL  : string  := "PARAMETER"
    );
    port(
        CLKOUT          : out    vl_logic;
        DELAY_OB        : out    vl_logic;
        CLKIN           : in     vl_logic;
        DELAY_STEP      : in     vl_logic_vector(7 downto 0);
        DIRECTION       : in     vl_logic;
        LOAD            : in     vl_logic;
        MOVE            : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of DELAY_STEP_VALUE : constant is 1;
    attribute mti_svvh_generic_type of SIM_DEVICE : constant is 1;
    attribute mti_svvh_generic_type of DELAY_STEP_SEL : constant is 1;
end GTP_IOCLKDELAY;
