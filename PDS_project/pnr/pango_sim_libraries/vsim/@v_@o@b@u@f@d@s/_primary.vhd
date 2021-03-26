library verilog;
use verilog.vl_types.all;
entity V_OBUFDS is
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
end V_OBUFDS;
