library verilog;
use verilog.vl_types.all;
entity tsmac_data_ram_v1_1 is
    generic(
        WR_ADDR_WIDTH   : integer := 11;
        RD_ADDR_WIDTH   : integer := 11
    );
    port(
        wr_data         : in     vl_logic_vector(8 downto 0);
        wr_addr         : in     vl_logic_vector;
        wr_en           : in     vl_logic;
        wr_clk          : in     vl_logic;
        wr_rst          : in     vl_logic;
        rd_data         : out    vl_logic_vector(8 downto 0);
        rd_addr         : in     vl_logic_vector;
        rd_clk          : in     vl_logic;
        rd_clk_en       : in     vl_logic;
        rd_rst          : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of WR_ADDR_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of RD_ADDR_WIDTH : constant is 1;
end tsmac_data_ram_v1_1;
