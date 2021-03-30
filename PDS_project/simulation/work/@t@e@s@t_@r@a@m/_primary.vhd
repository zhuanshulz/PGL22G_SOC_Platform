library verilog;
use verilog.vl_types.all;
entity TEST_RAM is
    port(
        wr_data         : in     vl_logic_vector(31 downto 0);
        wr_addr         : in     vl_logic_vector(7 downto 0);
        wr_en           : in     vl_logic;
        wr_clk          : in     vl_logic;
        wr_clk_en       : in     vl_logic;
        wr_rst          : in     vl_logic;
        rd_data         : out    vl_logic_vector(31 downto 0);
        rd_addr         : in     vl_logic_vector(7 downto 0);
        rd_clk          : in     vl_logic;
        rd_rst          : in     vl_logic
    );
end TEST_RAM;
