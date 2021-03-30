library verilog;
use verilog.vl_types.all;
entity GTP_IODELAY is
    generic(
        DELAY_STEP      : vl_logic_vector(6 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        DELAY_DEPTH     : integer := 7
    );
    port(
        DO              : out    vl_logic;
        DELAY_OB        : out    vl_logic;
        DI              : in     vl_logic;
        LOAD_N          : in     vl_logic;
        MOVE            : in     vl_logic;
        DIRECTION       : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of DELAY_STEP : constant is 2;
    attribute mti_svvh_generic_type of DELAY_DEPTH : constant is 2;
end GTP_IODELAY;
