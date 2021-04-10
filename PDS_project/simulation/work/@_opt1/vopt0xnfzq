library verilog;
use verilog.vl_types.all;
entity pgs_tsmac_rx_sm_v1_1 is
    generic(
        WR_ADDR_WIDTH   : integer := 11
    );
    port(
        rpd_i           : in     vl_logic_vector(7 downto 0);
        rpdv_i          : in     vl_logic;
        rpsf_i          : in     vl_logic;
        rpef_i          : in     vl_logic;
        rsvp_i          : in     vl_logic;
        rsv_i           : in     vl_logic_vector(32 downto 0);
        srrfn           : in     vl_logic;
        rx_clk          : in     vl_logic;
        clk_en          : in     vl_logic;
        hashe           : in     vl_logic;
        hashv           : in     vl_logic_vector(8 downto 0);
        dahash          : in     vl_logic_vector(8 downto 0);
        damac           : in     vl_logic_vector(47 downto 0);
        dmac            : in     vl_logic_vector(47 downto 0);
        fuc             : in     vl_logic;
        fmc             : in     vl_logic;
        fbc             : in     vl_logic;
        nfcs            : in     vl_logic;
        rdata           : out    vl_logic_vector(7 downto 0);
        rvalid          : out    vl_logic;
        rlast           : out    vl_logic;
        rsvp            : out    vl_logic;
        rsv             : out    vl_logic_vector(32 downto 0);
        packet_cnt      : out    vl_logic_vector(63 downto 0);
        crc_err_cnt     : out    vl_logic_vector(63 downto 0);
        pause_ctr_cnt   : out    vl_logic_vector(63 downto 0);
        addr_err_cnt    : out    vl_logic_vector(63 downto 0);
        len_err_cnt     : out    vl_logic_vector(63 downto 0);
        frame_trc_cnt   : out    vl_logic_vector(63 downto 0);
        ifg_sma_cnt     : out    vl_logic_vector(63 downto 0);
        bcad_cnt        : out    vl_logic_vector(63 downto 0);
        mcad_cnt        : out    vl_logic_vector(63 downto 0);
        ucad_cnt        : out    vl_logic_vector(63 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of WR_ADDR_WIDTH : constant is 1;
end pgs_tsmac_rx_sm_v1_1;
