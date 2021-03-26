library verilog;
use verilog.vl_types.all;
entity GTP_SPI is
    port(
        SCK_OE_N        : out    vl_logic;
        SCK_I           : in     vl_logic;
        SCK_O           : out    vl_logic;
        SS_O_N          : out    vl_logic_vector(7 downto 0);
        SS_I_N          : in     vl_logic;
        MISO_OE_N       : out    vl_logic;
        MISO_I          : in     vl_logic;
        MISO_O          : out    vl_logic;
        MOSI_OE_N       : out    vl_logic;
        MOSI_I          : in     vl_logic;
        MOSI_O          : out    vl_logic;
        IRQ             : out    vl_logic
    );
end GTP_SPI;
