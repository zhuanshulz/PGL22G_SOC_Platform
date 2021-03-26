library verilog;
use verilog.vl_types.all;
entity V_APM_E2 is
    generic(
        GRS_EN          : string  := "TRUE";
        USE_POSTADD     : integer := 0;
        USE_PREADD      : integer := 0;
        PREADD_REG      : integer := 0;
        X_REG           : integer := 0;
        CXO_REG         : integer := 0;
        XB_REG          : integer := 0;
        Y_REG           : integer := 0;
        Z_REG           : integer := 0;
        MULT_REG        : integer := 0;
        P_REG           : integer := 0;
        MODEY_REG       : integer := 0;
        MODEZ_REG       : integer := 0;
        MODEIN_REG      : integer := 0;
        X_SEL           : integer := 0;
        XB_SEL          : integer := 0;
        ASYNC_RST       : integer := 0;
        USE_SIMD        : integer := 0;
        P_INIT0         : vl_logic_vector(47 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        P_INIT1         : vl_logic_vector(47 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        ROUNDMODE_SEL   : integer := 0;
        CPO_REG         : integer := 0;
        USE_ACCLOW      : integer := 0;
        CIN_SEL         : integer := 0
    );
    port(
        P               : out    vl_logic_vector(47 downto 0);
        CPO             : out    vl_logic_vector(47 downto 0);
        COUT            : out    vl_logic;
        CXO             : out    vl_logic_vector(29 downto 0);
        CXBO            : out    vl_logic_vector(24 downto 0);
        X               : in     vl_logic_vector(29 downto 0);
        CXI             : in     vl_logic_vector(29 downto 0);
        CXBI            : in     vl_logic_vector(24 downto 0);
        XB              : in     vl_logic_vector(24 downto 0);
        Y               : in     vl_logic_vector(17 downto 0);
        Z               : in     vl_logic_vector(47 downto 0);
        CPI             : in     vl_logic_vector(47 downto 0);
        CIN             : in     vl_logic;
        MODEY           : in     vl_logic_vector(2 downto 0);
        MODEZ           : in     vl_logic_vector(3 downto 0);
        MODEIN          : in     vl_logic_vector(4 downto 0);
        CLK             : in     vl_logic;
        CEX1            : in     vl_logic;
        CEX2            : in     vl_logic;
        CEX3            : in     vl_logic;
        CEXB            : in     vl_logic;
        CEY1            : in     vl_logic;
        CEY2            : in     vl_logic;
        CEZ             : in     vl_logic;
        CEPRE           : in     vl_logic;
        CEM             : in     vl_logic;
        CEP             : in     vl_logic;
        CEMODEY         : in     vl_logic;
        CEMODEZ         : in     vl_logic;
        CEMODEIN        : in     vl_logic;
        RSTX            : in     vl_logic;
        RSTXB           : in     vl_logic;
        RSTY            : in     vl_logic;
        RSTZ            : in     vl_logic;
        RSTPRE          : in     vl_logic;
        RSTM            : in     vl_logic;
        RSTP            : in     vl_logic;
        RSTMODEY        : in     vl_logic;
        RSTMODEZ        : in     vl_logic;
        RSTMODEIN       : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of USE_POSTADD : constant is 1;
    attribute mti_svvh_generic_type of USE_PREADD : constant is 1;
    attribute mti_svvh_generic_type of PREADD_REG : constant is 1;
    attribute mti_svvh_generic_type of X_REG : constant is 1;
    attribute mti_svvh_generic_type of CXO_REG : constant is 1;
    attribute mti_svvh_generic_type of XB_REG : constant is 1;
    attribute mti_svvh_generic_type of Y_REG : constant is 1;
    attribute mti_svvh_generic_type of Z_REG : constant is 1;
    attribute mti_svvh_generic_type of MULT_REG : constant is 1;
    attribute mti_svvh_generic_type of P_REG : constant is 1;
    attribute mti_svvh_generic_type of MODEY_REG : constant is 1;
    attribute mti_svvh_generic_type of MODEZ_REG : constant is 1;
    attribute mti_svvh_generic_type of MODEIN_REG : constant is 1;
    attribute mti_svvh_generic_type of X_SEL : constant is 1;
    attribute mti_svvh_generic_type of XB_SEL : constant is 1;
    attribute mti_svvh_generic_type of ASYNC_RST : constant is 1;
    attribute mti_svvh_generic_type of USE_SIMD : constant is 1;
    attribute mti_svvh_generic_type of P_INIT0 : constant is 2;
    attribute mti_svvh_generic_type of P_INIT1 : constant is 2;
    attribute mti_svvh_generic_type of ROUNDMODE_SEL : constant is 1;
    attribute mti_svvh_generic_type of CPO_REG : constant is 1;
    attribute mti_svvh_generic_type of USE_ACCLOW : constant is 1;
    attribute mti_svvh_generic_type of CIN_SEL : constant is 1;
end V_APM_E2;
