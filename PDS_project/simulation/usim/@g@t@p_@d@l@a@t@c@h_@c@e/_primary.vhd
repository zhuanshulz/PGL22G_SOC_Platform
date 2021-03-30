library verilog;
use verilog.vl_types.all;
entity GTP_DLATCH_CE is
    generic(
        GRS_EN          : string  := "TRUE";
        INIT            : vl_logic := Hi0
    );
    port(
        Q               : out    vl_logic;
        D               : in     vl_logic;
        G               : in     vl_logic;
        C               : in     vl_logic;
        GE              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of INIT : constant is 1;
end GTP_DLATCH_CE;
