library verilog;
use verilog.vl_types.all;
entity V_LUT5CARRY2 is
    generic(
        INIT_A          : vl_logic_vector(31 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        ID_TO_LUT_A     : string  := "FALSE";
        CIN_TO_LUT_A    : string  := "TRUE";
        I4_TO_CARRY_A   : string  := "TRUE";
        I4_TO_LUT_A     : string  := "FALSE";
        INIT_B          : vl_logic_vector(31 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        ID_TO_LUT_B     : string  := "FALSE";
        CIN_TO_LUT_B    : string  := "TRUE";
        I4_TO_CARRY_B   : string  := "TRUE";
        I4_TO_LUT_B     : string  := "FALSE"
    );
    port(
        COUT            : out    vl_logic;
        FCOUT           : out    vl_logic;
        S0              : out    vl_logic;
        S1              : out    vl_logic;
        CIN             : in     vl_logic;
        A0              : in     vl_logic;
        AD              : in     vl_logic;
        A1              : in     vl_logic;
        A2              : in     vl_logic;
        A3              : in     vl_logic;
        A4              : in     vl_logic;
        B0              : in     vl_logic;
        BD              : in     vl_logic;
        B1              : in     vl_logic;
        B2              : in     vl_logic;
        B3              : in     vl_logic;
        B4              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of INIT_A : constant is 2;
    attribute mti_svvh_generic_type of ID_TO_LUT_A : constant is 1;
    attribute mti_svvh_generic_type of CIN_TO_LUT_A : constant is 1;
    attribute mti_svvh_generic_type of I4_TO_CARRY_A : constant is 1;
    attribute mti_svvh_generic_type of I4_TO_LUT_A : constant is 1;
    attribute mti_svvh_generic_type of INIT_B : constant is 2;
    attribute mti_svvh_generic_type of ID_TO_LUT_B : constant is 1;
    attribute mti_svvh_generic_type of CIN_TO_LUT_B : constant is 1;
    attribute mti_svvh_generic_type of I4_TO_CARRY_B : constant is 1;
    attribute mti_svvh_generic_type of I4_TO_LUT_B : constant is 1;
end V_LUT5CARRY2;
