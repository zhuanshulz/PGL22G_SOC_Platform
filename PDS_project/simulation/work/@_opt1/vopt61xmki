library verilog;
use verilog.vl_types.all;
entity pgs_tsmac_rgmii_gmii_convert_v1_0 is
    port(
        tx_rst          : in     vl_logic;
        rx_rst          : in     vl_logic;
        tx_clk          : in     vl_logic;
        tx_en_gm        : in     vl_logic;
        txd_gm          : in     vl_logic_vector(7 downto 0);
        tx_er_gm        : in     vl_logic;
        rx_clk          : in     vl_logic;
        rx_ctr          : in     vl_logic;
        col_rgm         : in     vl_logic;
        crs_rgm         : in     vl_logic;
        rxd_rgm         : in     vl_logic_vector(3 downto 0);
        txd_rgm         : out    vl_logic_vector(3 downto 0);
        tx_ctr          : out    vl_logic;
        col_gm          : out    vl_logic;
        crs_gm          : out    vl_logic;
        rx_dv_gm        : out    vl_logic;
        rx_er_gm        : out    vl_logic;
        rxd_gm          : out    vl_logic_vector(7 downto 0)
    );
end pgs_tsmac_rgmii_gmii_convert_v1_0;
