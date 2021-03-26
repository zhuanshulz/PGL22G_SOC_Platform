library verilog;
use verilog.vl_types.all;
entity GTP_DLL_E1 is
    generic(
        GRS_EN          : string  := "TRUE";
        FAST_LOCK       : string  := "TRUE";
        DELAY_STEP_OFFSET: integer := 0
    );
    port(
        DELAY_STEP      : out    vl_logic_vector(7 downto 0);
        DELAY_STEP1     : out    vl_logic_vector(7 downto 0);
        LOCK            : out    vl_logic;
        CLKIN           : in     vl_logic;
        UPDATE_N        : in     vl_logic;
        RST             : in     vl_logic;
        PWD             : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of FAST_LOCK : constant is 1;
    attribute mti_svvh_generic_type of DELAY_STEP_OFFSET : constant is 1;
end GTP_DLL_E1;
