library verilog;
use verilog.vl_types.all;
entity m1_soc_top is
    generic(
        TH_1S           : vl_logic_vector(0 to 26) := (Hi0, Hi0, Hi1, Hi1, Hi1, Hi1, Hi1, Hi0, Hi1, Hi1, Hi1, Hi1, Hi0, Hi0, Hi0, Hi1, Hi0, Hi1, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        ex_clk_50m      : in     vl_logic;
        rst_key         : in     vl_logic;
        gpio_in0        : in     vl_logic;
        gpio_in1        : in     vl_logic;
        LED             : out    vl_logic_vector(3 downto 0);
        RX              : in     vl_logic;
        TX              : out    vl_logic;
        spi0_clk        : out    vl_logic;
        spi0_cs         : out    vl_logic;
        spi0_mosi       : out    vl_logic;
        spi0_miso       : in     vl_logic;
        i2c0_sck        : inout  vl_logic;
        i2c0_sda        : inout  vl_logic;
        pad_loop_in     : in     vl_logic;
        pad_loop_in_h   : in     vl_logic;
        pad_rstn_ch0    : out    vl_logic;
        pad_ddr_clk_w   : out    vl_logic;
        pad_ddr_clkn_w  : out    vl_logic;
        pad_csn_ch0     : out    vl_logic;
        pad_addr_ch0    : out    vl_logic_vector(15 downto 0);
        pad_dq_ch0      : inout  vl_logic_vector(15 downto 0);
        pad_dqs_ch0     : inout  vl_logic_vector(1 downto 0);
        pad_dqsn_ch0    : inout  vl_logic_vector(1 downto 0);
        pad_dm_rdqs_ch0 : out    vl_logic_vector(1 downto 0);
        pad_cke_ch0     : out    vl_logic;
        pad_odt_ch0     : out    vl_logic;
        pad_rasn_ch0    : out    vl_logic;
        pad_casn_ch0    : out    vl_logic;
        pad_wen_ch0     : out    vl_logic;
        pad_ba_ch0      : out    vl_logic_vector(2 downto 0);
        pad_loop_out    : out    vl_logic;
        pad_loop_out_h  : out    vl_logic;
        rx_clki         : in     vl_logic;
        phy_rx_dv       : in     vl_logic;
        phy_rxd0        : in     vl_logic;
        phy_rxd1        : in     vl_logic;
        phy_rxd2        : in     vl_logic;
        phy_rxd3        : in     vl_logic;
        l0_sgmii_clk_shft: out    vl_logic;
        phy_tx_en       : out    vl_logic;
        phy_txd0        : out    vl_logic;
        phy_txd1        : out    vl_logic;
        phy_txd2        : out    vl_logic;
        phy_txd3        : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of TH_1S : constant is 1;
end m1_soc_top;
