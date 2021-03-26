library verilog;
use verilog.vl_types.all;
entity GTP_CLKBUFGMUX_E1 is
    generic(
        TRIGGER_MODE    : string  := "NEGEDGE";
        INIT_SEL        : string  := "CLK0"
    );
    port(
        CLKOUT          : out    vl_logic;
        CLKIN0          : in     vl_logic;
        CLKIN1          : in     vl_logic;
        SEL             : in     vl_logic;
        EN              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of TRIGGER_MODE : constant is 1;
    attribute mti_svvh_generic_type of INIT_SEL : constant is 1;
end GTP_CLKBUFGMUX_E1;
