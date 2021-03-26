library verilog;
use verilog.vl_types.all;
entity INT_PSE is
    generic(
        ASIZE           : integer := 9;
        SC_PSE          : vl_logic_vector
    );
    port(
        A               : in     vl_logic_vector;
        SIGN            : in     vl_logic;
        A_PSE           : out    vl_logic_vector
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of ASIZE : constant is 1;
    attribute mti_svvh_generic_type of SC_PSE : constant is 4;
end INT_PSE;
