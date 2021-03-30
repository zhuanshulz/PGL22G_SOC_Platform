library verilog;
use verilog.vl_types.all;
entity pgs_tsmac_rgmii_to_gmii_v1_0 is
    generic(
        TP              : integer := 1
    );
    port(
        rst_n           : in     vl_logic;
        rx_clk          : in     vl_logic;
        rx_ctr          : in     vl_logic;
        col_rgm         : in     vl_logic;
        crs_rgm         : in     vl_logic;
        rxd_rgm         : in     vl_logic_vector(3 downto 0);
        rx_dv_gm        : out    vl_logic;
        rx_er_gm        : out    vl_logic;
        col_gm          : out    vl_logic;
        crs_gm          : out    vl_logic;
        rxd_gm          : out    vl_logic_vector(7 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of TP : constant is 1;
end pgs_tsmac_rgmii_to_gmii_v1_0;
