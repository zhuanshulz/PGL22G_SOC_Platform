library verilog;
use verilog.vl_types.all;
entity GTP_GPLL is
    generic(
        CLKIN_FREQ      : real    := 5.000000e+001;
        LOCK_MODE       : vl_logic := Hi0;
        STATIC_RATIOI   : integer := 1;
        STATIC_RATIOM   : integer := 1;
        STATIC_RATIO0   : real    := 1.000000e+000;
        STATIC_RATIO1   : integer := 1;
        STATIC_RATIO2   : integer := 1;
        STATIC_RATIO3   : integer := 1;
        STATIC_RATIO4   : integer := 1;
        STATIC_RATIO5   : integer := 1;
        STATIC_RATIO6   : integer := 1;
        STATIC_RATIOF   : real    := 1.000000e+000;
        STATIC_DUTY0    : integer := 2;
        STATIC_DUTY1    : integer := 2;
        STATIC_DUTY2    : integer := 2;
        STATIC_DUTY3    : integer := 2;
        STATIC_DUTY4    : integer := 2;
        STATIC_DUTY5    : integer := 2;
        STATIC_DUTY6    : integer := 2;
        STATIC_DUTYF    : integer := 2;
        STATIC_PHASE    : integer := 0;
        STATIC_PHASE0   : integer := 0;
        STATIC_PHASE1   : integer := 0;
        STATIC_PHASE2   : integer := 0;
        STATIC_PHASE3   : integer := 0;
        STATIC_PHASE4   : integer := 0;
        STATIC_PHASE5   : integer := 0;
        STATIC_PHASE6   : integer := 0;
        STATIC_PHASEF   : integer := 0;
        STATIC_CPHASE0  : integer := 0;
        STATIC_CPHASE1  : integer := 0;
        STATIC_CPHASE2  : integer := 0;
        STATIC_CPHASE3  : integer := 0;
        STATIC_CPHASE4  : integer := 0;
        STATIC_CPHASE5  : integer := 0;
        STATIC_CPHASE6  : integer := 0;
        STATIC_CPHASEF  : integer := 0;
        CLK_DPS0_EN     : string  := "FALSE";
        CLK_DPS1_EN     : string  := "FALSE";
        CLK_DPS2_EN     : string  := "FALSE";
        CLK_DPS3_EN     : string  := "FALSE";
        CLK_DPS4_EN     : string  := "FALSE";
        CLK_DPS5_EN     : string  := "FALSE";
        CLK_DPS6_EN     : string  := "FALSE";
        CLK_DPSF_EN     : string  := "FALSE";
        CLK_CAS5_EN     : string  := "FALSE";
        CLKOUT0_SYN_EN  : string  := "FALSE";
        CLKOUT1_SYN_EN  : string  := "FALSE";
        CLKOUT2_SYN_EN  : string  := "FALSE";
        CLKOUT3_SYN_EN  : string  := "FALSE";
        CLKOUT4_SYN_EN  : string  := "FALSE";
        CLKOUT5_SYN_EN  : string  := "FALSE";
        CLKOUT6_SYN_EN  : string  := "FALSE";
        CLKOUTF_SYN_EN  : string  := "FALSE";
        SSC_MODE        : string  := "DISABLE";
        SSC_FREQ        : real    := 5.000000e+001;
        INTERNAL_FB     : string  := "CLKOUTF";
        EXTERNAL_FB     : string  := "DISABLE";
        BANDWIDTH       : string  := "OPTIMIZED"
    );
    port(
        CLKOUT0         : out    vl_logic;
        CLKOUT0N        : out    vl_logic;
        CLKOUT1         : out    vl_logic;
        CLKOUT1N        : out    vl_logic;
        CLKOUT2         : out    vl_logic;
        CLKOUT2N        : out    vl_logic;
        CLKOUT3         : out    vl_logic;
        CLKOUT3N        : out    vl_logic;
        CLKOUT4         : out    vl_logic;
        CLKOUT5         : out    vl_logic;
        CLKOUT6         : out    vl_logic;
        CLKOUTF         : out    vl_logic;
        CLKOUTFN        : out    vl_logic;
        LOCK            : out    vl_logic;
        DPS_DONE        : out    vl_logic;
        APB_RDATA       : out    vl_logic_vector(15 downto 0);
        APB_READY       : out    vl_logic;
        CLKIN1          : in     vl_logic;
        CLKIN2          : in     vl_logic;
        CLKFB           : in     vl_logic;
        CLKIN_SEL       : in     vl_logic;
        DPS_CLK         : in     vl_logic;
        DPS_EN          : in     vl_logic;
        DPS_DIR         : in     vl_logic;
        CLKOUT0_SYN     : in     vl_logic;
        CLKOUT1_SYN     : in     vl_logic;
        CLKOUT2_SYN     : in     vl_logic;
        CLKOUT3_SYN     : in     vl_logic;
        CLKOUT4_SYN     : in     vl_logic;
        CLKOUT5_SYN     : in     vl_logic;
        CLKOUT6_SYN     : in     vl_logic;
        CLKOUTF_SYN     : in     vl_logic;
        PLL_PWD         : in     vl_logic;
        RST             : in     vl_logic;
        APB_CLK         : in     vl_logic;
        APB_RST_N       : in     vl_logic;
        APB_ADDR        : in     vl_logic_vector(4 downto 0);
        APB_SEL         : in     vl_logic;
        APB_EN          : in     vl_logic;
        APB_WRITE       : in     vl_logic;
        APB_WDATA       : in     vl_logic_vector(15 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of CLKIN_FREQ : constant is 2;
    attribute mti_svvh_generic_type of LOCK_MODE : constant is 1;
    attribute mti_svvh_generic_type of STATIC_RATIOI : constant is 2;
    attribute mti_svvh_generic_type of STATIC_RATIOM : constant is 2;
    attribute mti_svvh_generic_type of STATIC_RATIO0 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_RATIO1 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_RATIO2 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_RATIO3 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_RATIO4 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_RATIO5 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_RATIO6 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_RATIOF : constant is 2;
    attribute mti_svvh_generic_type of STATIC_DUTY0 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_DUTY1 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_DUTY2 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_DUTY3 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_DUTY4 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_DUTY5 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_DUTY6 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_DUTYF : constant is 2;
    attribute mti_svvh_generic_type of STATIC_PHASE : constant is 2;
    attribute mti_svvh_generic_type of STATIC_PHASE0 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_PHASE1 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_PHASE2 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_PHASE3 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_PHASE4 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_PHASE5 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_PHASE6 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_PHASEF : constant is 2;
    attribute mti_svvh_generic_type of STATIC_CPHASE0 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_CPHASE1 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_CPHASE2 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_CPHASE3 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_CPHASE4 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_CPHASE5 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_CPHASE6 : constant is 2;
    attribute mti_svvh_generic_type of STATIC_CPHASEF : constant is 2;
    attribute mti_svvh_generic_type of CLK_DPS0_EN : constant is 1;
    attribute mti_svvh_generic_type of CLK_DPS1_EN : constant is 1;
    attribute mti_svvh_generic_type of CLK_DPS2_EN : constant is 1;
    attribute mti_svvh_generic_type of CLK_DPS3_EN : constant is 1;
    attribute mti_svvh_generic_type of CLK_DPS4_EN : constant is 1;
    attribute mti_svvh_generic_type of CLK_DPS5_EN : constant is 1;
    attribute mti_svvh_generic_type of CLK_DPS6_EN : constant is 1;
    attribute mti_svvh_generic_type of CLK_DPSF_EN : constant is 1;
    attribute mti_svvh_generic_type of CLK_CAS5_EN : constant is 1;
    attribute mti_svvh_generic_type of CLKOUT0_SYN_EN : constant is 1;
    attribute mti_svvh_generic_type of CLKOUT1_SYN_EN : constant is 1;
    attribute mti_svvh_generic_type of CLKOUT2_SYN_EN : constant is 1;
    attribute mti_svvh_generic_type of CLKOUT3_SYN_EN : constant is 1;
    attribute mti_svvh_generic_type of CLKOUT4_SYN_EN : constant is 1;
    attribute mti_svvh_generic_type of CLKOUT5_SYN_EN : constant is 1;
    attribute mti_svvh_generic_type of CLKOUT6_SYN_EN : constant is 1;
    attribute mti_svvh_generic_type of CLKOUTF_SYN_EN : constant is 1;
    attribute mti_svvh_generic_type of SSC_MODE : constant is 1;
    attribute mti_svvh_generic_type of SSC_FREQ : constant is 2;
    attribute mti_svvh_generic_type of INTERNAL_FB : constant is 1;
    attribute mti_svvh_generic_type of EXTERNAL_FB : constant is 1;
    attribute mti_svvh_generic_type of BANDWIDTH : constant is 1;
end GTP_GPLL;
