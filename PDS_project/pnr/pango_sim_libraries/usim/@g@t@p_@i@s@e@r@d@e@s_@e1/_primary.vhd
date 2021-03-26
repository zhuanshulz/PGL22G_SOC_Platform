library verilog;
use verilog.vl_types.all;
entity GTP_ISERDES_E1 is
    generic(
        ISERDES_MODE    : string  := "IDES4";
        GRS_EN          : string  := "TRUE"
    );
    port(
        DO              : out    vl_logic_vector(7 downto 0);
        DI              : in     vl_logic;
        ICLK            : in     vl_logic;
        RCLK            : in     vl_logic;
        ALIGNWD         : in     vl_logic;
        RST             : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of ISERDES_MODE : constant is 1;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
end GTP_ISERDES_E1;
