library verilog;
use verilog.vl_types.all;
entity GTP_IOBUF_TX_MIPI is
    generic(
        IOSTANDARD      : string  := "DEFAULT";
        SLEW_RATE       : string  := "SLOW";
        DRIVE_STRENGTH  : string  := "6";
        TERM_DIFF       : string  := "ON"
    );
    port(
        O_LP            : out    vl_logic;
        OB_LP           : out    vl_logic;
        IO              : inout  vl_logic;
        IOB             : inout  vl_logic;
        I_HS            : in     vl_logic;
        I_LP            : in     vl_logic;
        IB_LP           : in     vl_logic;
        T               : in     vl_logic;
        TB              : in     vl_logic;
        M               : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of IOSTANDARD : constant is 1;
    attribute mti_svvh_generic_type of SLEW_RATE : constant is 1;
    attribute mti_svvh_generic_type of DRIVE_STRENGTH : constant is 1;
    attribute mti_svvh_generic_type of TERM_DIFF : constant is 1;
end GTP_IOBUF_TX_MIPI;
