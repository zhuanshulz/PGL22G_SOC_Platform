library verilog;
use verilog.vl_types.all;
entity GTP_PREADD_FIR_A is
    generic(
        GRS_EN          : string  := "TRUE";
        SYNC_RST        : string  := "FALSE";
        INREG_EN        : string  := "TRUE";
        INREG_Z1_EN     : string  := "TRUE";
        OUTREG_EN       : string  := "TRUE";
        INPUT_OP        : vl_logic_vector(0 to 7) := (Hi1, Hi1, Hi0, Hi0, Hi0, Hi1, Hi1, Hi0);
        DYN_OP_SEL      : vl_logic_vector(0 to 7) := (Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1);
        OPCD_DYN_SEL    : vl_logic := Hi0;
        OPCD_CPI_SEL    : vl_logic := Hi0
    );
    port(
        CYO             : out    vl_logic_vector(17 downto 0);
        CYO_SIGNED      : out    vl_logic;
        CPO             : out    vl_logic_vector(63 downto 0);
        CPO_SIGNED      : out    vl_logic;
        CZO             : out    vl_logic_vector(17 downto 0);
        CZO_SIGNED      : out    vl_logic;
        P               : out    vl_logic_vector(63 downto 0);
        CE              : in     vl_logic;
        RST             : in     vl_logic;
        CLK             : in     vl_logic;
        CYI             : in     vl_logic_vector(17 downto 0);
        CYI_SIGNED      : in     vl_logic;
        Y0              : in     vl_logic_vector(17 downto 0);
        Y0_SIGNED       : in     vl_logic;
        Z0              : in     vl_logic_vector(17 downto 0);
        Z0_SIGNED       : in     vl_logic;
        H0              : in     vl_logic_vector(17 downto 0);
        H0_SIGNED       : in     vl_logic;
        H1              : in     vl_logic_vector(17 downto 0);
        H1_SIGNED       : in     vl_logic;
        Y1              : in     vl_logic_vector(17 downto 0);
        Y1_SIGNED       : in     vl_logic;
        Z1              : in     vl_logic_vector(17 downto 0);
        Z1_SIGNED       : in     vl_logic;
        CZI             : in     vl_logic_vector(17 downto 0);
        CZI_SIGNED      : in     vl_logic;
        CPI             : in     vl_logic_vector(63 downto 0);
        CPI_SIGNED      : in     vl_logic;
        S0              : in     vl_logic;
        S1              : in     vl_logic;
        DYN_OP          : in     vl_logic_vector(5 downto 0);
        OPCD_CPI_DYN    : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of SYNC_RST : constant is 1;
    attribute mti_svvh_generic_type of INREG_EN : constant is 1;
    attribute mti_svvh_generic_type of INREG_Z1_EN : constant is 1;
    attribute mti_svvh_generic_type of OUTREG_EN : constant is 1;
    attribute mti_svvh_generic_type of INPUT_OP : constant is 1;
    attribute mti_svvh_generic_type of DYN_OP_SEL : constant is 1;
    attribute mti_svvh_generic_type of OPCD_DYN_SEL : constant is 1;
    attribute mti_svvh_generic_type of OPCD_CPI_SEL : constant is 1;
end GTP_PREADD_FIR_A;
