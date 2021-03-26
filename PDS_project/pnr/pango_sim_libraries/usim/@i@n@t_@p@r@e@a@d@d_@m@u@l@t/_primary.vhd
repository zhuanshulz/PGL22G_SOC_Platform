library verilog;
use verilog.vl_types.all;
entity INT_PREADD_MULT is
    generic(
        GRS_EN          : string  := "FALSE";
        SYNC_RST        : string  := "FALSE";
        INREG_EN        : string  := "FALSE";
        PREREG_EN       : string  := "FALSE";
        OUTREG_EN       : string  := "FALSE";
        ASIZE           : integer := 18;
        BSIZE           : integer := 18;
        SC_PSE_A        : vl_logic_vector;
        SC_PSE_B        : vl_logic_vector;
        SC_PSE_C        : vl_logic_vector;
        PREADD_EN       : integer := 1;
        PSIZE           : vl_logic_vector(31 downto 0)
    );
    port(
        CE              : in     vl_logic;
        CLK             : in     vl_logic;
        RST             : in     vl_logic;
        A_SIGNED        : in     vl_logic;
        A               : in     vl_logic_vector;
        B_SIGNED        : in     vl_logic;
        B               : in     vl_logic_vector;
        C_SIGNED        : in     vl_logic;
        C               : in     vl_logic_vector;
        PREADDSUB       : in     vl_logic;
        P               : out    vl_logic_vector
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of SYNC_RST : constant is 1;
    attribute mti_svvh_generic_type of INREG_EN : constant is 1;
    attribute mti_svvh_generic_type of PREREG_EN : constant is 1;
    attribute mti_svvh_generic_type of OUTREG_EN : constant is 1;
    attribute mti_svvh_generic_type of ASIZE : constant is 2;
    attribute mti_svvh_generic_type of BSIZE : constant is 2;
    attribute mti_svvh_generic_type of SC_PSE_A : constant is 4;
    attribute mti_svvh_generic_type of SC_PSE_B : constant is 4;
    attribute mti_svvh_generic_type of SC_PSE_C : constant is 4;
    attribute mti_svvh_generic_type of PREADD_EN : constant is 2;
    attribute mti_svvh_generic_type of PSIZE : constant is 4;
end INT_PREADD_MULT;
