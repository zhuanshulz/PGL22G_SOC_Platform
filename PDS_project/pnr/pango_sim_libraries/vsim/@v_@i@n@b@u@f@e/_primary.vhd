library verilog;
use verilog.vl_types.all;
entity V_INBUFE is
    generic(
        IOSTANDARD      : string  := "DEFAULT";
        TERM_DDR        : string  := "ON"
    );
    port(
        O               : out    vl_logic;
        EN              : in     vl_logic;
        I               : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of IOSTANDARD : constant is 1;
    attribute mti_svvh_generic_type of TERM_DDR : constant is 1;
end V_INBUFE;
