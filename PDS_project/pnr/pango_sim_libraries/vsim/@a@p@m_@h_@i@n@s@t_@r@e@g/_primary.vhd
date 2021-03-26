library verilog;
use verilog.vl_types.all;
entity APM_H_INST_REG is
    generic(
        SIZE            : integer := 19
    );
    port(
        IN_SEL          : in     vl_logic;
        BYP             : in     vl_logic;
        D0              : in     vl_logic_vector;
        D1              : in     vl_logic_vector;
        CLK             : in     vl_logic;
        CE              : in     vl_logic;
        ARST            : in     vl_logic;
        SRST            : in     vl_logic;
        Q               : out    vl_logic_vector
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of SIZE : constant is 1;
end APM_H_INST_REG;
