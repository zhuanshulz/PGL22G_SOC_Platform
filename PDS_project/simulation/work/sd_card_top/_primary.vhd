library verilog;
use verilog.vl_types.all;
entity sd_card_top is
    port(
        HCLK            : in     vl_logic;
        cs              : in     vl_logic;
        rst             : in     vl_logic;
        wr_en           : in     vl_logic;
        wr_data         : in     vl_logic_vector(31 downto 0);
        waddr           : in     vl_logic_vector(21 downto 0);
        rd_addr         : in     vl_logic_vector(21 downto 0);
        rd_en           : in     vl_logic;
        SD_nCS          : out    vl_logic;
        SD_DCLK         : out    vl_logic;
        SD_MOSI         : out    vl_logic;
        SD_MISO         : in     vl_logic;
        rd_data         : out    vl_logic_vector(31 downto 0)
    );
end sd_card_top;
