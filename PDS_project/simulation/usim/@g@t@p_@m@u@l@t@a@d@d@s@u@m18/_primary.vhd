library verilog;
use verilog.vl_types.all;
entity GTP_MULTADDSUM18 is
    generic(
        GRS_EN          : string  := "TRUE";
        SYNC_RST        : string  := "FALSE";
        INREG_EN        : string  := "FALSE";
        PIPEREG_EN      : string  := "FALSE";
        OUTREG_EN       : string  := "FALSE";
        ADDSUB_OP       : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        SUM_ADDSUB_OP   : integer := 0;
        DYN_ADDSUB_OP   : vl_logic_vector(0 to 1) := (Hi1, Hi1);
        DYN_SUM_ADDSUB_OP: integer := 1
    );
    port(
        P               : out    vl_logic_vector(37 downto 0);
        CE              : in     vl_logic;
        RST             : in     vl_logic;
        CLK             : in     vl_logic;
        A_SIGNED        : in     vl_logic_vector(1 downto 0);
        A0              : in     vl_logic_vector(17 downto 0);
        A1              : in     vl_logic_vector(17 downto 0);
        A2              : in     vl_logic_vector(17 downto 0);
        A3              : in     vl_logic_vector(17 downto 0);
        B_SIGNED        : in     vl_logic_vector(1 downto 0);
        B0              : in     vl_logic_vector(17 downto 0);
        B1              : in     vl_logic_vector(17 downto 0);
        B2              : in     vl_logic_vector(17 downto 0);
        B3              : in     vl_logic_vector(17 downto 0);
        ADDSUB          : in     vl_logic_vector(1 downto 0);
        SUM_ADDSUB      : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of SYNC_RST : constant is 1;
    attribute mti_svvh_generic_type of INREG_EN : constant is 1;
    attribute mti_svvh_generic_type of PIPEREG_EN : constant is 1;
    attribute mti_svvh_generic_type of OUTREG_EN : constant is 1;
    attribute mti_svvh_generic_type of ADDSUB_OP : constant is 1;
    attribute mti_svvh_generic_type of SUM_ADDSUB_OP : constant is 1;
    attribute mti_svvh_generic_type of DYN_ADDSUB_OP : constant is 1;
    attribute mti_svvh_generic_type of DYN_SUM_ADDSUB_OP : constant is 1;
end GTP_MULTADDSUM18;
