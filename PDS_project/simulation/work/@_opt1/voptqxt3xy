library verilog;
use verilog.vl_types.all;
entity pgs_tsmac_gmii_to_rgmii_v1_0 is
    generic(
        TP              : integer := 1
    );
    port(
        rst_n           : in     vl_logic;
        tx_clk          : in     vl_logic;
        tx_en_gm        : in     vl_logic;
        tx_er_gm        : in     vl_logic;
        txd_gm          : in     vl_logic_vector(7 downto 0);
        tx_ctr          : out    vl_logic;
        txd_rgm         : out    vl_logic_vector(3 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of TP : constant is 1;
end pgs_tsmac_gmii_to_rgmii_v1_0;
