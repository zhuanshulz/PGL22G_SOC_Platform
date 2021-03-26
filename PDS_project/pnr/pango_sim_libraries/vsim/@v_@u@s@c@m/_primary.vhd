library verilog;
use verilog.vl_types.all;
entity V_USCM is
    generic(
        USCM_MODE       : string  := "BUGCE";
        SIM_DEVICE      : string  := "TITAN"
    );
    port(
        CLK0            : in     vl_logic;
        CLK1            : in     vl_logic;
        SEL             : in     vl_logic;
        CLKOUT          : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of USCM_MODE : constant is 1;
    attribute mti_svvh_generic_type of SIM_DEVICE : constant is 1;
end V_USCM;
