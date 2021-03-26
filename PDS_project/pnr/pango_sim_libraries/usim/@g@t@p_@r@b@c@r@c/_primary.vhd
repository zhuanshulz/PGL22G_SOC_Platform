library verilog;
use verilog.vl_types.all;
entity GTP_RBCRC is
    port(
        CLK             : in     vl_logic;
        RST             : in     vl_logic;
        START           : in     vl_logic;
        SEC_START       : in     vl_logic;
        ERR             : out    vl_logic;
        VALID           : out    vl_logic;
        SEC_OVER        : out    vl_logic
    );
end GTP_RBCRC;
