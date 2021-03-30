library verilog;
use verilog.vl_types.all;
entity GTP_MULTADDACC18 is
    generic(
        GRS_EN          : string  := "TRUE";
        SYNC_RST        : string  := "FALSE";
        INREG_EN        : string  := "FALSE";
        PIPEREG_EN      : string  := "FALSE";
        ADDSUB_OP       : integer := 0;
        ACC_ADDSUB_OP   : integer := 0;
        DYN_ADDSUB_OP   : integer := 1;
        DYN_ACC_ADDSUB_OP: integer := 1;
        OVERFLOW_MASK   : vl_logic_vector(0 to 63) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        PATTERN         : vl_logic_vector(0 to 63) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        MASKPAT         : vl_logic_vector(0 to 63) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        DYN_ACC_INIT    : integer := 0;
        ACC_INIT_VALUE  : vl_logic_vector(0 to 63) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        P               : out    vl_logic_vector(63 downto 0);
        OVER            : out    vl_logic;
        UNDER           : out    vl_logic;
        EQZ             : out    vl_logic;
        EQZM            : out    vl_logic;
        EQOM            : out    vl_logic;
        EQPAT           : out    vl_logic;
        EQPATN          : out    vl_logic;
        CE              : in     vl_logic;
        RST             : in     vl_logic;
        CLK             : in     vl_logic;
        A_SIGNED        : in     vl_logic;
        A0              : in     vl_logic_vector(17 downto 0);
        A1              : in     vl_logic_vector(17 downto 0);
        B_SIGNED        : in     vl_logic;
        B0              : in     vl_logic_vector(17 downto 0);
        B1              : in     vl_logic_vector(17 downto 0);
        ACC_INIT        : in     vl_logic_vector(63 downto 0);
        ADDSUB          : in     vl_logic;
        ACC_ADDSUB      : in     vl_logic;
        RELOAD          : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of SYNC_RST : constant is 1;
    attribute mti_svvh_generic_type of INREG_EN : constant is 1;
    attribute mti_svvh_generic_type of PIPEREG_EN : constant is 1;
    attribute mti_svvh_generic_type of ADDSUB_OP : constant is 1;
    attribute mti_svvh_generic_type of ACC_ADDSUB_OP : constant is 1;
    attribute mti_svvh_generic_type of DYN_ADDSUB_OP : constant is 1;
    attribute mti_svvh_generic_type of DYN_ACC_ADDSUB_OP : constant is 1;
    attribute mti_svvh_generic_type of OVERFLOW_MASK : constant is 1;
    attribute mti_svvh_generic_type of PATTERN : constant is 1;
    attribute mti_svvh_generic_type of MASKPAT : constant is 1;
    attribute mti_svvh_generic_type of DYN_ACC_INIT : constant is 1;
    attribute mti_svvh_generic_type of ACC_INIT_VALUE : constant is 1;
end GTP_MULTADDACC18;
