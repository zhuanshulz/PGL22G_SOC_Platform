library verilog;
use verilog.vl_types.all;
entity GTP_TIMER is
    port(
        RST_N           : in     vl_logic;
        CLK             : in     vl_logic;
        STAMP           : in     vl_logic;
        PWM             : out    vl_logic;
        IRQ             : out    vl_logic
    );
end GTP_TIMER;
