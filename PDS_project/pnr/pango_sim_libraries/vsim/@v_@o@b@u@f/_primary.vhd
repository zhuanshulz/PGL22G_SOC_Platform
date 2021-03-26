library verilog;
use verilog.vl_types.all;
entity V_OBUF is
    generic(
        IOSTANDARD      : string  := "DEFAULT";
        SLEW_RATE       : string  := "SLOW";
        DRIVE_STRENGTH  : string  := "8"
    );
    port(
        O               : out    vl_logic;
        I               : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of IOSTANDARD : constant is 1;
    attribute mti_svvh_generic_type of SLEW_RATE : constant is 1;
    attribute mti_svvh_generic_type of DRIVE_STRENGTH : constant is 1;
end V_OBUF;
