library verilog;
use verilog.vl_types.all;
entity GTP_OSC_E1 is
    generic(
        CLK_DIV         : integer := 2
    );
    port(
        CLKOUT          : out    vl_logic;
        EN              : in     vl_logic;
        RST_N           : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of CLK_DIV : constant is 2;
end GTP_OSC_E1;
