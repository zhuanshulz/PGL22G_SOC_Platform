library verilog;
use verilog.vl_types.all;
entity GTP_ZEROHOLDDELAY is
    generic(
        ZHOLD_SET       : string  := "NODELAY"
    );
    port(
        DO              : out    vl_logic;
        DI              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of ZHOLD_SET : constant is 1;
end GTP_ZEROHOLDDELAY;
