library verilog;
use verilog.vl_types.all;
entity GTP_APB is
    generic(
        IDCODE          : vl_logic_vector(31 downto 0) := (Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1);
        USERCODE        : vl_logic_vector(31 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        CLK             : in     vl_logic;
        RST_N           : in     vl_logic;
        ADDR            : in     vl_logic_vector(4 downto 0);
        SEL_CCS         : in     vl_logic;
        SEL_SPI         : in     vl_logic;
        SEL_I2C0        : in     vl_logic;
        SEL_I2C1        : in     vl_logic;
        SEL_TIMER       : in     vl_logic;
        SEL_PLL0        : in     vl_logic;
        SEL_PLL1        : in     vl_logic;
        EN              : in     vl_logic;
        WR              : in     vl_logic;
        WDATA           : in     vl_logic_vector(7 downto 0);
        RDATA           : out    vl_logic_vector(7 downto 0);
        RDY             : out    vl_logic;
        IRQ             : out    vl_logic;
        IRQ_CCS         : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of IDCODE : constant is 2;
    attribute mti_svvh_generic_type of USERCODE : constant is 2;
end GTP_APB;
