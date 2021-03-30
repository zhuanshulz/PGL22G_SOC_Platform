library verilog;
use verilog.vl_types.all;
entity GTP_IOBUF is
    generic(
        IOSTANDARD      : string  := "DEFAULT";
        SLEW_RATE       : string  := "SLOW";
        DRIVE_STRENGTH  : string  := "8";
        TERM_DDR        : string  := "ON"
    );
    port(
        O               : out    vl_logic;
        IO              : inout  vl_logic;
        I               : in     vl_logic;
        T               : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of IOSTANDARD : constant is 1;
    attribute mti_svvh_generic_type of SLEW_RATE : constant is 1;
    attribute mti_svvh_generic_type of DRIVE_STRENGTH : constant is 1;
    attribute mti_svvh_generic_type of TERM_DDR : constant is 1;
end GTP_IOBUF;
