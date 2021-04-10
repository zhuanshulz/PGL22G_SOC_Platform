library verilog;
use verilog.vl_types.all;
entity GTP_OSERDES is
    generic(
        OSERDES_MODE    : string  := "ODDR";
        WL_EXTEND       : string  := "FALSE";
        GRS_EN          : string  := "TRUE";
        LRS_EN          : string  := "TRUE";
        TSDDR_INIT      : vl_logic := Hi0
    );
    port(
        DO              : out    vl_logic;
        TQ              : out    vl_logic;
        DI              : in     vl_logic_vector(7 downto 0);
        TI              : in     vl_logic_vector(3 downto 0);
        RCLK            : in     vl_logic;
        SERCLK          : in     vl_logic;
        OCLK            : in     vl_logic;
        RST             : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of OSERDES_MODE : constant is 1;
    attribute mti_svvh_generic_type of WL_EXTEND : constant is 1;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of LRS_EN : constant is 1;
    attribute mti_svvh_generic_type of TSDDR_INIT : constant is 1;
end GTP_OSERDES;
