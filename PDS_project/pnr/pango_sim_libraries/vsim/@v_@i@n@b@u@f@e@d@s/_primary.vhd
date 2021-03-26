library verilog;
use verilog.vl_types.all;
entity V_INBUFEDS is
    generic(
        IOSTANDARD      : string  := "DEFAULT";
        TERM_DIFF       : string  := "ON"
    );
    port(
        O               : out    vl_logic;
        EN              : in     vl_logic;
        I               : in     vl_logic;
        IB              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of IOSTANDARD : constant is 1;
    attribute mti_svvh_generic_type of TERM_DIFF : constant is 1;
end V_INBUFEDS;
