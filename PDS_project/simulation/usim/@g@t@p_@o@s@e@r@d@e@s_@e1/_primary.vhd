library verilog;
use verilog.vl_types.all;
entity GTP_OSERDES_E1 is
    generic(
        OSERDES_MODE    : string  := "OSER4";
        GRS_EN          : string  := "TRUE"
    );
    port(
        DO              : out    vl_logic;
        DI              : in     vl_logic_vector(7 downto 0);
        RCLK            : in     vl_logic;
        OCLK            : in     vl_logic;
        RST             : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of OSERDES_MODE : constant is 1;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
end GTP_OSERDES_E1;
