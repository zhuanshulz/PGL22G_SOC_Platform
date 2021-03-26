library verilog;
use verilog.vl_types.all;
entity V_IPAL_E1 is
    generic(
        IDCODE          : vl_logic_vector(31 downto 0) := (Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1);
        DATA_WIDTH      : string  := "X8";
        SIM_DEVICE      : string  := "PGL25G"
    );
    port(
        DO              : out    vl_logic_vector(31 downto 0);
        RBCRC_ERR       : out    vl_logic;
        RBCRC_VALID     : out    vl_logic;
        ECC_VALID       : out    vl_logic;
        ECC_INDEX       : out    vl_logic_vector(11 downto 0);
        SERROR          : out    vl_logic;
        DERROR          : out    vl_logic;
        BUSY            : out    vl_logic;
        RST_N           : in     vl_logic;
        CLK             : in     vl_logic;
        CS_N            : in     vl_logic;
        RW_SEL          : in     vl_logic;
        DI              : in     vl_logic_vector(31 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of IDCODE : constant is 2;
    attribute mti_svvh_generic_type of DATA_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of SIM_DEVICE : constant is 1;
end V_IPAL_E1;
