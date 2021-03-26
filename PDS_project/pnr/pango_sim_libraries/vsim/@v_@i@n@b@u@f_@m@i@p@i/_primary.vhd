library verilog;
use verilog.vl_types.all;
entity V_INBUF_MIPI is
    generic(
        MIPI_MODE       : string  := "MASTER";
        IOSTANDARD      : string  := "DEFAULT";
        TERM_DIFF       : string  := "ON"
    );
    port(
        O               : out    vl_logic;
        I               : in     vl_logic;
        IB              : in     vl_logic;
        TS              : in     vl_logic;
        M               : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of MIPI_MODE : constant is 1;
    attribute mti_svvh_generic_type of IOSTANDARD : constant is 1;
    attribute mti_svvh_generic_type of TERM_DIFF : constant is 1;
end V_INBUF_MIPI;
