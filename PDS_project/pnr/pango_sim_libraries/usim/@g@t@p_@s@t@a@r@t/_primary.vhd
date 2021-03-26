library verilog;
use verilog.vl_types.all;
entity GTP_START is
    port(
        CLK             : in     vl_logic;
        GOE             : in     vl_logic;
        GRS_N           : in     vl_logic;
        GWE             : in     vl_logic
    );
end GTP_START;
