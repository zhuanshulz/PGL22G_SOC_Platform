library verilog;
use verilog.vl_types.all;
entity INT_FLAG is
    generic(
        GRS_EN          : string  := "FALSE";
        SYNC_RST        : string  := "FALSE";
        PSIZE           : integer := 64;
        PATSIZE         : integer := 64;
        MASKPATSIZE     : integer := 64;
        OUTREG_EN       : string  := "TRUE"
    );
    port(
        CE              : in     vl_logic;
        RST             : in     vl_logic;
        CLK             : in     vl_logic;
        P               : in     vl_logic_vector;
        PATTERN         : in     vl_logic_vector;
        MASKPAT         : in     vl_logic_vector;
        OVERFLOW_MASK   : in     vl_logic_vector;
        R               : in     vl_logic_vector;
        eqz             : out    vl_logic;
        eqzm            : out    vl_logic;
        eqom            : out    vl_logic;
        eqpat           : out    vl_logic;
        eqpatn          : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of SYNC_RST : constant is 1;
    attribute mti_svvh_generic_type of PSIZE : constant is 1;
    attribute mti_svvh_generic_type of PATSIZE : constant is 1;
    attribute mti_svvh_generic_type of MASKPATSIZE : constant is 1;
    attribute mti_svvh_generic_type of OUTREG_EN : constant is 1;
end INT_FLAG;
