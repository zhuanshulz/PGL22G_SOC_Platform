library verilog;
use verilog.vl_types.all;
entity GTP_DCC is
    generic(
        GRS_EN          : string  := "TRUE";
        SAMPLE_CLKDIV_FACTOR: string  := "2"
    );
    port(
        SAMPLE_CLKOUT   : out    vl_logic;
        PROBE_CLKOUT    : out    vl_logic;
        SAMPLE_CLKDIVOUT: out    vl_logic;
        CLKOUT_CTRL     : in     vl_logic_vector(2 downto 0);
        CLKIN0          : in     vl_logic;
        CLKIN1          : in     vl_logic;
        RST             : in     vl_logic;
        CLK0_SEL        : in     vl_logic_vector(1 downto 0);
        CLK1_SEL        : in     vl_logic_vector(1 downto 0);
        DELAY_STEP0     : in     vl_logic_vector(7 downto 0);
        DELAY_STEP1     : in     vl_logic_vector(7 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of SAMPLE_CLKDIV_FACTOR : constant is 1;
end GTP_DCC;
