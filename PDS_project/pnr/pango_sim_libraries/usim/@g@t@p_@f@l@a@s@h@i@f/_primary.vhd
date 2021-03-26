library verilog;
use verilog.vl_types.all;
entity GTP_FLASHIF is
    port(
        EN_N            : in     vl_logic;
        CLK             : in     vl_logic;
        CS_N            : in     vl_logic;
        DIN             : in     vl_logic_vector(3 downto 0);
        DOUT_EN_N       : in     vl_logic_vector(2 downto 0);
        DOUT            : out    vl_logic_vector(3 downto 0)
    );
end GTP_FLASHIF;
