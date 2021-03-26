library verilog;
use verilog.vl_types.all;
entity GTP_CLKBUFGCE is
    generic(
        DEFAULT_VALUE   : vl_logic := Hi0;
        SIM_DEVICE      : string  := "TITAN"
    );
    port(
        CLKOUT          : out    vl_logic;
        CLKIN           : in     vl_logic;
        CE              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of DEFAULT_VALUE : constant is 1;
    attribute mti_svvh_generic_type of SIM_DEVICE : constant is 1;
end GTP_CLKBUFGCE;
