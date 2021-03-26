library verilog;
use verilog.vl_types.all;
entity V_LAASYN is
    generic(
        GRS_EN          : string  := "TRUE";
        SET_RESET       : string  := "SET";
        LRS_EN          : string  := "FALSE";
        CLK_POL         : string  := "FALSE"
    );
    port(
        Q               : out    vl_logic;
        D               : in     vl_logic;
        CK              : in     vl_logic;
        SR              : in     vl_logic;
        CE              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of SET_RESET : constant is 1;
    attribute mti_svvh_generic_type of LRS_EN : constant is 1;
    attribute mti_svvh_generic_type of CLK_POL : constant is 1;
end V_LAASYN;
