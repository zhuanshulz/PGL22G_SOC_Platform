library verilog;
use verilog.vl_types.all;
entity V_OUTBUFT_MIPI_SLAVE is
    generic(
        IOSTANDARD      : string  := "DEFAULT";
        DRIVE_STRENGTH  : string  := "6";
        SLEW_RATE       : string  := "SLOW"
    );
    port(
        OB              : out    vl_logic;
        I               : in     vl_logic;
        IB              : in     vl_logic;
        TB              : in     vl_logic;
        M               : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of IOSTANDARD : constant is 1;
    attribute mti_svvh_generic_type of DRIVE_STRENGTH : constant is 1;
    attribute mti_svvh_generic_type of SLEW_RATE : constant is 1;
end V_OUTBUFT_MIPI_SLAVE;
