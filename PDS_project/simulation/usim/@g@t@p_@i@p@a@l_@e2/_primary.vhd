library verilog;
use verilog.vl_types.all;
entity GTP_IPAL_E2 is
    generic(
        SIM_DEVICE      : string  := "PG2L100H";
        IDCODE          : vl_logic_vector(31 downto 0) := (Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1);
        DATA_WIDTH      : string  := "X8"
    );
    port(
        DO              : out    vl_logic_vector(31 downto 0);
        RBCRC_ERR       : out    vl_logic;
        RBCRC_VALID     : out    vl_logic;
        ECC_VALID       : out    vl_logic;
        ECC_INDEX       : out    vl_logic_vector(11 downto 0);
        SERROR          : out    vl_logic;
        DERROR          : out    vl_logic;
        SEU_FRAME_ADDR  : out    vl_logic_vector(7 downto 0);
        SEU_COLUMN_ADDR : out    vl_logic_vector(7 downto 0);
        SEU_REGION_ADDR : out    vl_logic_vector(4 downto 0);
        SEU_FRAME_NADDR : out    vl_logic_vector(7 downto 0);
        SEU_COLUMN_NADDR: out    vl_logic_vector(7 downto 0);
        SEU_REGION_NADDR: out    vl_logic_vector(4 downto 0);
        PRCFG_OVER      : out    vl_logic;
        PRCFG_ERR       : out    vl_logic;
        DRCFG_OVER      : out    vl_logic;
        DRCFG_ERR       : out    vl_logic;
        RST_N           : in     vl_logic;
        CLK             : in     vl_logic;
        CS_N            : in     vl_logic;
        RW_SEL          : in     vl_logic;
        DI              : in     vl_logic_vector(31 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of SIM_DEVICE : constant is 1;
    attribute mti_svvh_generic_type of IDCODE : constant is 2;
    attribute mti_svvh_generic_type of DATA_WIDTH : constant is 1;
end GTP_IPAL_E2;
