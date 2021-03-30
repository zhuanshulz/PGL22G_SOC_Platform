library verilog;
use verilog.vl_types.all;
entity GTP_I2C is
    generic(
        I2C_NUM         : integer := 0
    );
    port(
        SCL_I           : in     vl_logic;
        SCL_O           : out    vl_logic;
        SDA_I           : in     vl_logic;
        SDA_O           : out    vl_logic;
        IRQ             : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of I2C_NUM : constant is 1;
end GTP_I2C;
