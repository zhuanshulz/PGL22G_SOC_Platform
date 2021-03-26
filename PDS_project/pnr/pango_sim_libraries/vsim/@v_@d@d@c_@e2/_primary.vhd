library verilog;
use verilog.vl_types.all;
entity V_DDC_E2 is
    generic(
        CLKA_GATE_EN    : string  := "FALSE";
        WCLK_DELAY_SEL  : string  := "FALSE";
        DDC_MODE        : string  := "QUAD_RATE";
        R_EXTEND        : string  := "FALSE";
        DELAY_SEL       : vl_logic := Hi0;
        GRS_EN          : string  := "TRUE";
        IFIFO_GENERIC   : string  := "FALSE";
        RADDR_INIT      : vl_logic_vector(2 downto 0) := (Hi0, Hi0, Hi0);
        DATA_RATE       : vl_logic_vector(1 downto 0) := (Hi0, Hi0)
    );
    port(
        WCLK            : out    vl_logic;
        WCLK_DELAY      : out    vl_logic;
        DQSI_DELAY      : out    vl_logic;
        DQSIB_DELAY     : out    vl_logic;
        DGTS            : out    vl_logic;
        IFIFO_WADDR     : out    vl_logic_vector(2 downto 0);
        IFIFO_RADDR     : out    vl_logic_vector(2 downto 0);
        READ_VALID      : out    vl_logic;
        DQS_DRIFT       : out    vl_logic_vector(1 downto 0);
        DRIFT_DETECT_ERR: out    vl_logic;
        DQS_DRIFT_STATUS: out    vl_logic;
        DQS_SAMPLE      : out    vl_logic;
        RST             : in     vl_logic;
        RST_TRAINING_N  : in     vl_logic;
        CLKA            : in     vl_logic;
        CLKB            : in     vl_logic;
        DQSI            : in     vl_logic;
        DQSIB           : in     vl_logic;
        DELAY_STEP0     : in     vl_logic_vector(7 downto 0);
        DELAY_STEP1     : in     vl_logic_vector(7 downto 0);
        DELAY_STEP2     : in     vl_logic_vector(7 downto 0);
        DELAY_STEP3     : in     vl_logic_vector(7 downto 0);
        DELAY_STEP4     : in     vl_logic_vector(7 downto 0);
        DQS_GATE_CTRL   : in     vl_logic_vector(3 downto 0);
        GATE_SEL        : in     vl_logic;
        CLK_GATE_CTRL   : in     vl_logic_vector(1 downto 0);
        CLKA_GATE       : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of CLKA_GATE_EN : constant is 1;
    attribute mti_svvh_generic_type of WCLK_DELAY_SEL : constant is 1;
    attribute mti_svvh_generic_type of DDC_MODE : constant is 1;
    attribute mti_svvh_generic_type of R_EXTEND : constant is 1;
    attribute mti_svvh_generic_type of DELAY_SEL : constant is 1;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of IFIFO_GENERIC : constant is 1;
    attribute mti_svvh_generic_type of RADDR_INIT : constant is 2;
    attribute mti_svvh_generic_type of DATA_RATE : constant is 2;
end V_DDC_E2;
