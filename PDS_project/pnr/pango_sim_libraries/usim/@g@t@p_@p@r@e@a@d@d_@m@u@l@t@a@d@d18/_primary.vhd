library verilog;
use verilog.vl_types.all;
entity GTP_PREADD_MULTADD18 is
    generic(
        GRS_EN          : string  := "TRUE";
        SYNC_RST        : string  := "FALSE";
        INREG_EN        : string  := "FALSE";
        PREREG_EN       : string  := "FALSE";
        PIPEREG_EN      : string  := "FALSE";
        OUTREG_EN       : string  := "FALSE";
        ADDSUB_OP       : integer := 0;
        DYN_ADDSUB_OP   : integer := 1
    );
    port(
        P               : out    vl_logic_vector(37 downto 0);
        CE              : in     vl_logic;
        RST             : in     vl_logic;
        CLK             : in     vl_logic;
        A0              : in     vl_logic_vector(17 downto 0);
        A1              : in     vl_logic_vector(17 downto 0);
        B0              : in     vl_logic_vector(17 downto 0);
        B1              : in     vl_logic_vector(17 downto 0);
        C0              : in     vl_logic_vector(17 downto 0);
        C1              : in     vl_logic_vector(17 downto 0);
        A_SIGNED        : in     vl_logic;
        B_SIGNED        : in     vl_logic;
        C_SIGNED        : in     vl_logic;
        PREADDSUB       : in     vl_logic_vector(1 downto 0);
        ADDSUB          : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of SYNC_RST : constant is 1;
    attribute mti_svvh_generic_type of INREG_EN : constant is 1;
    attribute mti_svvh_generic_type of PREREG_EN : constant is 1;
    attribute mti_svvh_generic_type of PIPEREG_EN : constant is 1;
    attribute mti_svvh_generic_type of OUTREG_EN : constant is 1;
    attribute mti_svvh_generic_type of ADDSUB_OP : constant is 1;
    attribute mti_svvh_generic_type of DYN_ADDSUB_OP : constant is 1;
end GTP_PREADD_MULTADD18;
