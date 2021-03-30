library verilog;
use verilog.vl_types.all;
entity GTP_PREADD_MULT27 is
    generic(
        GRS_EN          : string  := "TRUE";
        SYNC_RST        : string  := "FALSE";
        INREG_EN        : string  := "FALSE";
        PREREG_EN       : string  := "FALSE";
        OUTREG_EN       : string  := "FALSE"
    );
    port(
        P               : out    vl_logic_vector(53 downto 0);
        CE              : in     vl_logic;
        RST             : in     vl_logic;
        CLK             : in     vl_logic;
        A_SIGNED        : in     vl_logic;
        A               : in     vl_logic_vector(26 downto 0);
        B_SIGNED        : in     vl_logic;
        B               : in     vl_logic_vector(25 downto 0);
        C_SIGNED        : in     vl_logic;
        C               : in     vl_logic_vector(25 downto 0);
        PREADDSUB       : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of SYNC_RST : constant is 1;
    attribute mti_svvh_generic_type of INREG_EN : constant is 1;
    attribute mti_svvh_generic_type of PREREG_EN : constant is 1;
    attribute mti_svvh_generic_type of OUTREG_EN : constant is 1;
end GTP_PREADD_MULT27;
