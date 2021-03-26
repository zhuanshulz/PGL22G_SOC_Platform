library verilog;
use verilog.vl_types.all;
entity GTP_CLKBUFXCE is
    generic(
        TRIGGER_MODE    : string  := "POSEDGE";
        CE_TYPE         : string  := "SYNC";
        CE_INV          : string  := "FALSE"
    );
    port(
        CLKOUT          : out    vl_logic;
        CLKIN           : in     vl_logic;
        CE              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of TRIGGER_MODE : constant is 1;
    attribute mti_svvh_generic_type of CE_TYPE : constant is 1;
    attribute mti_svvh_generic_type of CE_INV : constant is 1;
end GTP_CLKBUFXCE;
