library verilog;
use verilog.vl_types.all;
entity INT_REG is
    generic(
        SIZE            : integer := 1
    );
    port(
        D               : in     vl_logic_vector;
        BYPASS          : in     vl_logic;
        CLK             : in     vl_logic;
        CE              : in     vl_logic;
        ARST            : in     vl_logic;
        SRST            : in     vl_logic;
        Q               : out    vl_logic_vector
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of SIZE : constant is 1;
end INT_REG;
