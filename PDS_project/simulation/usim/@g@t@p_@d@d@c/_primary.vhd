library verilog;
use verilog.vl_types.all;
entity GTP_DDC is
    generic(
        GRS_EN          : string  := "TRUE";
        DDC_MODE        : string  := "FULL_RATE";
        IFIFO_GENERIC   : string  := "FALSE";
        WCLK_DELAY_OFFSET: vl_logic_vector(0 to 8) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        DQSI_DELAY_OFFSET: vl_logic_vector(0 to 8) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        CLKA_GATE_EN    : string  := "FALSE";
        R_DELAY_STEP_EN : string  := "TRUE";
        R_MOVE_EN       : string  := "FALSE";
        W_MOVE_EN       : string  := "FALSE";
        R_EXTEND        : string  := "FALSE";
        RADDR_INIT      : vl_logic_vector(0 to 2) := (Hi0, Hi0, Hi0)
    );
    port(
        WDELAY_OB       : out    vl_logic;
        WCLK            : out    vl_logic;
        WCLK_DELAY      : out    vl_logic;
        RDELAY_OB       : out    vl_logic;
        DQSI_DELAY      : out    vl_logic;
        DGTS            : out    vl_logic;
        READ_VALID      : out    vl_logic;
        IFIFO_WADDR     : out    vl_logic_vector(2 downto 0);
        IFIFO_RADDR     : out    vl_logic_vector(2 downto 0);
        RST             : in     vl_logic;
        CLKB            : in     vl_logic;
        CLKA            : in     vl_logic;
        CLKA_GATE       : in     vl_logic;
        DELAY_STEP1     : in     vl_logic_vector(7 downto 0);
        DELAY_STEP0     : in     vl_logic_vector(7 downto 0);
        W_DIRECTION     : in     vl_logic;
        W_MOVE          : in     vl_logic;
        W_LOAD_N        : in     vl_logic;
        DQS_GATE_CTRL   : in     vl_logic_vector(3 downto 0);
        READ_CLK_CTRL   : in     vl_logic_vector(2 downto 0);
        DQSI            : in     vl_logic;
        R_DIRECTION     : in     vl_logic;
        R_MOVE          : in     vl_logic;
        R_LOAD_N        : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of DDC_MODE : constant is 1;
    attribute mti_svvh_generic_type of IFIFO_GENERIC : constant is 1;
    attribute mti_svvh_generic_type of WCLK_DELAY_OFFSET : constant is 1;
    attribute mti_svvh_generic_type of DQSI_DELAY_OFFSET : constant is 1;
    attribute mti_svvh_generic_type of CLKA_GATE_EN : constant is 1;
    attribute mti_svvh_generic_type of R_DELAY_STEP_EN : constant is 1;
    attribute mti_svvh_generic_type of R_MOVE_EN : constant is 1;
    attribute mti_svvh_generic_type of W_MOVE_EN : constant is 1;
    attribute mti_svvh_generic_type of R_EXTEND : constant is 1;
    attribute mti_svvh_generic_type of RADDR_INIT : constant is 1;
end GTP_DDC;
