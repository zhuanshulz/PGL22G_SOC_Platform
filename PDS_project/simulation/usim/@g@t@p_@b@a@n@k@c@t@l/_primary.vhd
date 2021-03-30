library verilog;
use verilog.vl_types.all;
entity GTP_BANKCTL is
    generic(
        DIFFO_DYN_EN    : string  := "FALSE";
        DIFFI_DYN_EN    : string  := "FLASE";
        BANK_LOC        : string  := "BK0"
    );
    port(
        OE_N            : in     vl_logic;
        IE_N            : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of DIFFO_DYN_EN : constant is 1;
    attribute mti_svvh_generic_type of DIFFI_DYN_EN : constant is 1;
    attribute mti_svvh_generic_type of BANK_LOC : constant is 1;
end GTP_BANKCTL;
