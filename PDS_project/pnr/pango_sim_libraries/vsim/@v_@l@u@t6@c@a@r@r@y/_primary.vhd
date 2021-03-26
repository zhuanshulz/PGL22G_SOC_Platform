library verilog;
use verilog.vl_types.all;
entity V_LUT6CARRY is
    generic(
        INIT            : vl_logic_vector(63 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        I5_TO_CARRY     : string  := "TRUE";
        I5_TO_LUT       : string  := "FALSE"
    );
    port(
        COUT            : out    vl_logic;
        Z               : out    vl_logic;
        Z5              : out    vl_logic;
        CIN             : in     vl_logic;
        I0              : in     vl_logic;
        I1              : in     vl_logic;
        I2              : in     vl_logic;
        I3              : in     vl_logic;
        I4              : in     vl_logic;
        I5              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of INIT : constant is 2;
    attribute mti_svvh_generic_type of I5_TO_CARRY : constant is 1;
    attribute mti_svvh_generic_type of I5_TO_LUT : constant is 1;
end V_LUT6CARRY;
