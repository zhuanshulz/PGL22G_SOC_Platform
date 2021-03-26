library verilog;
use verilog.vl_types.all;
entity GTP_CLKBUFGMUX is
    generic(
        TRIGGER_MODE    : string  := "NORMAL";
        SIM_DEVICE      : string  := "TITAN"
    );
    port(
        CLKOUT          : out    vl_logic;
        CLKIN0          : in     vl_logic;
        CLKIN1          : in     vl_logic;
        SEL             : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of TRIGGER_MODE : constant is 1;
    attribute mti_svvh_generic_type of SIM_DEVICE : constant is 1;
end GTP_CLKBUFGMUX;
