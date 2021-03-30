library verilog;
use verilog.vl_types.all;
entity ipml_reg_fifo_v1_0 is
    generic(
        W               : integer := 8
    );
    port(
        clk             : in     vl_logic;
        rst_n           : in     vl_logic;
        data_in_valid   : in     vl_logic;
        data_in         : in     vl_logic_vector;
        data_in_ready   : out    vl_logic;
        data_out_ready  : in     vl_logic;
        data_out        : out    vl_logic_vector;
        data_out_valid  : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of W : constant is 1;
end ipml_reg_fifo_v1_0;
