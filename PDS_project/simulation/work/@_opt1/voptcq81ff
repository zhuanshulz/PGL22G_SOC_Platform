library verilog;
use verilog.vl_types.all;
entity m1_test is
    generic(
        CLKIN_FREQ      : real    := 5.000000e+001;
        DDR_TYPE        : string  := "DDR3";
        DATA_WIDTH      : string  := "16BIT";
        PLL_REFCLK_IN_PERIOD: vl_notype
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of CLKIN_FREQ : constant is 2;
    attribute mti_svvh_generic_type of DDR_TYPE : constant is 1;
    attribute mti_svvh_generic_type of DATA_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of PLL_REFCLK_IN_PERIOD : constant is 3;
end m1_test;
