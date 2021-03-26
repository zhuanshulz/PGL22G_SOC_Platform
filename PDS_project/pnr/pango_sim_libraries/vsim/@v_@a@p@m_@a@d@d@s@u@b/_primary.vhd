library verilog;
use verilog.vl_types.all;
entity V_APM_ADDSUB is
    generic(
        SIZE            : integer := 1
    );
    port(
        A               : in     vl_logic_vector;
        A_SIGNED        : in     vl_logic;
        B               : in     vl_logic_vector;
        B_SIGNED        : in     vl_logic;
        ADDSUB          : in     vl_logic;
        P               : out    vl_logic_vector;
        P_SIGNED        : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of SIZE : constant is 1;
end V_APM_ADDSUB;
