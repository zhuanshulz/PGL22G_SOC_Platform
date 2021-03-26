library verilog;
use verilog.vl_types.all;
entity GTP_ISERDES_E2 is
    generic(
        ISERDES_MODE    : string  := "SDR1TO4";
        CASCADE_MODE    : string  := "MASTER";
        BITSLIP_EN      : string  := "FALSE";
        GRS_EN          : string  := "TRUE";
        NUM_ICE         : vl_logic := Hi0;
        GRS_TYPE_Q0     : string  := "RESET";
        GRS_TYPE_Q1     : string  := "RESET";
        GRS_TYPE_Q2     : string  := "RESET";
        GRS_TYPE_Q3     : string  := "RESET";
        LRS_TYPE_Q0     : string  := "ASYNC_RESET";
        LRS_TYPE_Q1     : string  := "ASYNC_RESET";
        LRS_TYPE_Q2     : string  := "ASYNC_RESET";
        LRS_TYPE_Q3     : string  := "ASYNC_RESET"
    );
    port(
        RST             : in     vl_logic;
        ICE0            : in     vl_logic;
        ICE1            : in     vl_logic;
        DESCLK          : in     vl_logic;
        ICLK            : in     vl_logic;
        OCLK            : in     vl_logic;
        ICLKDIV         : in     vl_logic;
        DI              : in     vl_logic;
        BITSLIP         : in     vl_logic;
        ISHIFTIN0       : in     vl_logic;
        ISHIFTIN1       : in     vl_logic;
        IFIFO_WADDR     : in     vl_logic_vector(2 downto 0);
        IFIFO_RADDR     : in     vl_logic_vector(2 downto 0);
        DO              : out    vl_logic_vector(7 downto 0);
        ISHIFTOUT0      : out    vl_logic;
        ISHIFTOUT1      : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of ISERDES_MODE : constant is 1;
    attribute mti_svvh_generic_type of CASCADE_MODE : constant is 1;
    attribute mti_svvh_generic_type of BITSLIP_EN : constant is 1;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of NUM_ICE : constant is 1;
    attribute mti_svvh_generic_type of GRS_TYPE_Q0 : constant is 1;
    attribute mti_svvh_generic_type of GRS_TYPE_Q1 : constant is 1;
    attribute mti_svvh_generic_type of GRS_TYPE_Q2 : constant is 1;
    attribute mti_svvh_generic_type of GRS_TYPE_Q3 : constant is 1;
    attribute mti_svvh_generic_type of LRS_TYPE_Q0 : constant is 1;
    attribute mti_svvh_generic_type of LRS_TYPE_Q1 : constant is 1;
    attribute mti_svvh_generic_type of LRS_TYPE_Q2 : constant is 1;
    attribute mti_svvh_generic_type of LRS_TYPE_Q3 : constant is 1;
end GTP_ISERDES_E2;
