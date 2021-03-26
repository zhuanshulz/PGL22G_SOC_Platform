library verilog;
use verilog.vl_types.all;
entity V_FIFO9K is
    generic(
        GRS_EN          : string  := "TRUE";
        DATA_WIDTH      : integer := 9;
        DO_REG          : integer := 0;
        ALMOST_FULL_OFFSET: vl_logic_vector(12 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        ALMOST_EMPTY_OFFSET: vl_logic_vector(12 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        USE_EMPTY       : integer := 0;
        USE_FULL        : integer := 0;
        SYNC_FIFO       : string  := "FALSE"
    );
    port(
        ALMOST_EMPTY    : out    vl_logic;
        ALMOST_FULL     : out    vl_logic;
        EMPTY           : out    vl_logic;
        FULL            : out    vl_logic;
        WCNT            : out    vl_logic_vector(12 downto 0);
        RCNT            : out    vl_logic_vector(12 downto 0);
        DO              : out    vl_logic_vector(17 downto 0);
        DI              : in     vl_logic_vector(17 downto 0);
        WCLK            : in     vl_logic;
        RCLK            : in     vl_logic;
        WCE             : in     vl_logic;
        RCE             : in     vl_logic;
        ORCE            : in     vl_logic;
        RST             : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of DATA_WIDTH : constant is 2;
    attribute mti_svvh_generic_type of DO_REG : constant is 2;
    attribute mti_svvh_generic_type of ALMOST_FULL_OFFSET : constant is 2;
    attribute mti_svvh_generic_type of ALMOST_EMPTY_OFFSET : constant is 2;
    attribute mti_svvh_generic_type of USE_EMPTY : constant is 2;
    attribute mti_svvh_generic_type of USE_FULL : constant is 2;
    attribute mti_svvh_generic_type of SYNC_FIFO : constant is 1;
end V_FIFO9K;
