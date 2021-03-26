library verilog;
use verilog.vl_types.all;
entity GTP_FIFO36K_E1 is
    generic(
        GRS_EN          : string  := "TRUE";
        DATA_WIDTH      : integer := 18;
        DO_REG          : integer := 0;
        ECC_WRITE_EN    : string  := "FALSE";
        ECC_READ_EN     : string  := "FALSE";
        ALMOST_FULL_OFFSET: vl_logic_vector(14 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        ALMOST_EMPTY_OFFSET: vl_logic_vector(14 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        RST_VAL         : vl_logic_vector(71 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        USE_EMPTY       : integer := 0;
        USE_FULL        : integer := 0;
        SYNC_FIFO       : string  := "FALSE"
    );
    port(
        ALMOST_EMPTY    : out    vl_logic;
        ALMOST_FULL     : out    vl_logic;
        EMPTY           : out    vl_logic;
        FULL            : out    vl_logic;
        DO              : out    vl_logic_vector(71 downto 0);
        DI              : in     vl_logic_vector(71 downto 0);
        WCLK            : in     vl_logic;
        RCLK            : in     vl_logic;
        WCE             : in     vl_logic;
        RCE             : in     vl_logic;
        ORCE            : in     vl_logic;
        RST             : in     vl_logic;
        INJECT_SBITERR  : in     vl_logic;
        INJECT_DBITERR  : in     vl_logic;
        ECC_SBITERR     : out    vl_logic;
        ECC_DBITERR     : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of DATA_WIDTH : constant is 2;
    attribute mti_svvh_generic_type of DO_REG : constant is 2;
    attribute mti_svvh_generic_type of ECC_WRITE_EN : constant is 1;
    attribute mti_svvh_generic_type of ECC_READ_EN : constant is 1;
    attribute mti_svvh_generic_type of ALMOST_FULL_OFFSET : constant is 2;
    attribute mti_svvh_generic_type of ALMOST_EMPTY_OFFSET : constant is 2;
    attribute mti_svvh_generic_type of RST_VAL : constant is 2;
    attribute mti_svvh_generic_type of USE_EMPTY : constant is 2;
    attribute mti_svvh_generic_type of USE_FULL : constant is 2;
    attribute mti_svvh_generic_type of SYNC_FIFO : constant is 1;
end GTP_FIFO36K_E1;
