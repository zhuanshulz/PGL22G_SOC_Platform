library verilog;
use verilog.vl_types.all;
entity V_APM_REG is
    generic(
        REG_EN          : string  := "FALSE";
        SIZE            : integer := 1
    );
    port(
        CLK             : in     vl_logic;
        CE              : in     vl_logic;
        SRST            : in     vl_logic;
        ARST            : in     vl_logic;
        D               : in     vl_logic_vector;
        Q               : out    vl_logic_vector
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of REG_EN : constant is 1;
    attribute mti_svvh_generic_type of SIZE : constant is 1;
end V_APM_REG;
