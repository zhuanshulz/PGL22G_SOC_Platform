library verilog;
use verilog.vl_types.all;
entity GTP_OUTBUFCO is
    generic(
        IOSTANDARD      : string  := "DEFAULT"
    );
    port(
        O               : out    vl_logic;
        OB              : out    vl_logic;
        I               : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of IOSTANDARD : constant is 1;
end GTP_OUTBUFCO;
