library verilog;
use verilog.vl_types.all;
entity V_RES_CAL_E1 is
    generic(
        VCCIO           : string  := "1.2V";
        VREF_RATIO      : real    := 0.500000;
        CAL_ENABLE      : string  := "FALSE";
        CAL_CASCADE     : string  := "LOCAL";
        CASC_V_ENABLE   : string  := "FALSE"
    );
    port(
        PCODE_IN        : in     vl_logic_vector(4 downto 0);
        NCODE_IN        : in     vl_logic_vector(4 downto 0);
        SAMPLE_IN       : in     vl_logic;
        EN              : in     vl_logic;
        CODE_SEL        : in     vl_logic;
        RST             : in     vl_logic;
        PCODE_OUT       : out    vl_logic_vector(4 downto 0);
        NCODE_OUT       : out    vl_logic_vector(4 downto 0);
        SAMPLE_OUT      : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of VCCIO : constant is 1;
    attribute mti_svvh_generic_type of VREF_RATIO : constant is 1;
    attribute mti_svvh_generic_type of CAL_ENABLE : constant is 1;
    attribute mti_svvh_generic_type of CAL_CASCADE : constant is 1;
    attribute mti_svvh_generic_type of CASC_V_ENABLE : constant is 1;
end V_RES_CAL_E1;
