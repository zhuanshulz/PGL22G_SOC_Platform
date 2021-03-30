library verilog;
use verilog.vl_types.all;
entity DCACHE_SRAM0 is
    port(
        wr_data         : in     vl_logic_vector(31 downto 0);
        wr_addr         : in     vl_logic_vector(8 downto 0);
        wr_en           : in     vl_logic;
        wr_clk          : in     vl_logic;
        wr_rst          : in     vl_logic;
        wr_byte_en      : in     vl_logic_vector(3 downto 0);
        rd_data         : out    vl_logic_vector(31 downto 0);
        rd_addr         : in     vl_logic_vector(8 downto 0);
        rd_clk          : in     vl_logic;
        rd_rst          : in     vl_logic
    );
end DCACHE_SRAM0;
