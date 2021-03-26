library verilog;
use verilog.vl_types.all;
entity V_DLL_E2 is
    generic(
        GRS_EN          : string  := "TRUE";
        CAL_INIT        : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi1, Hi1, Hi1, Hi1);
        DELAY_STEP_OFFSET: integer := 0;
        DELAY_SEL       : vl_logic := Hi0;
        FAST_LOCK       : string  := "FALSE";
        FDIV            : vl_logic_vector(1 downto 0) := (Hi0, Hi1);
        INT_CLK         : vl_logic := Hi0;
        UPD_DLY         : vl_logic_vector(1 downto 0) := (Hi0, Hi0)
    );
    port(
        CLKIN           : in     vl_logic;
        SYS_CLK         : in     vl_logic;
        PWD             : in     vl_logic;
        RST             : in     vl_logic;
        UPDATE_N        : in     vl_logic;
        LOCK            : out    vl_logic;
        DELAY_STEP      : out    vl_logic_vector(7 downto 0);
        DELAY_STEP1     : out    vl_logic_vector(7 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of CAL_INIT : constant is 2;
    attribute mti_svvh_generic_type of DELAY_STEP_OFFSET : constant is 1;
    attribute mti_svvh_generic_type of DELAY_SEL : constant is 1;
    attribute mti_svvh_generic_type of FAST_LOCK : constant is 1;
    attribute mti_svvh_generic_type of FDIV : constant is 2;
    attribute mti_svvh_generic_type of INT_CLK : constant is 1;
    attribute mti_svvh_generic_type of UPD_DLY : constant is 2;
end V_DLL_E2;
