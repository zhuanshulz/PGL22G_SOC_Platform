library verilog;
use verilog.vl_types.all;
entity ipsl_hmic_h_ddrc_top_v1_1 is
    generic(
        TRFC_MIN        : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi1, Hi1, Hi0, Hi0);
        TREFI           : vl_logic_vector(11 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi1, Hi0, Hi0, Hi0, Hi1, Hi0);
        T_MRD           : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        T_MOD           : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        DDR_TYPE        : string  := "DDR3";
        MR              : vl_logic_vector(15 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0);
        EMR             : vl_logic_vector(15 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1);
        EMR2            : vl_logic_vector(15 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        EMR3            : vl_logic_vector(15 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        WR2PRE          : vl_logic_vector(6 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi1, Hi1, Hi1);
        T_FAW           : vl_logic_vector(5 downto 0) := (Hi0, Hi1, Hi0, Hi0, Hi0, Hi0);
        T_RAS_MAX       : vl_logic_vector(6 downto 0) := (Hi0, Hi0, Hi1, Hi1, Hi0, Hi1, Hi1);
        T_RAS_MIN       : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi1, Hi1, Hi1, Hi1);
        T_XP            : vl_logic_vector(4 downto 0) := (Hi0, Hi1, Hi0, Hi0, Hi0);
        RD2PRE          : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi0);
        T_RC            : vl_logic_vector(6 downto 0) := (Hi0, Hi0, Hi1, Hi0, Hi1, Hi0, Hi0);
        WL              : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi1);
        RL              : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi1);
        RD2WR           : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi1, Hi0);
        WR2RD           : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi1, Hi1, Hi0, Hi1);
        T_RCD           : vl_logic_vector(4 downto 0) := (Hi0, Hi0, Hi1, Hi0, Hi1);
        T_CCD           : vl_logic_vector(3 downto 0) := (Hi0, Hi1, Hi0, Hi0);
        T_RRD           : vl_logic_vector(3 downto 0) := (Hi0, Hi1, Hi0, Hi0);
        T_RP            : vl_logic_vector(4 downto 0) := (Hi0, Hi0, Hi1, Hi0, Hi1);
        T_CKSRX         : vl_logic_vector(3 downto 0) := (Hi0, Hi1, Hi0, Hi1);
        T_CKSRE         : vl_logic_vector(3 downto 0) := (Hi0, Hi1, Hi0, Hi1);
        T_CKESR         : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi0);
        T_CKE           : vl_logic_vector(4 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi1);
        DFI_T_RDDATA_EN : vl_logic_vector(6 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0);
        DFI_TPHY_WRLAT  : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0);
        DATA_BUS_WIDTH  : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        ADDRESS_MAPPING_SEL: integer := 0;
        MEM_ROW_ADDRESS : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi1, Hi1, Hi0);
        MEM_COLUMN_ADDRESS: vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi1, Hi0);
        MEM_BANK_ADDRESS: vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi1, Hi1)
    );
    port(
        resetn          : in     vl_logic;
        ddrc_init_done  : out    vl_logic;
        core_clk        : in     vl_logic;
        ddrc_rst        : in     vl_logic;
        areset_0        : in     vl_logic;
        aclk_0          : in     vl_logic;
        awid_0          : in     vl_logic_vector(7 downto 0);
        awaddr_0        : in     vl_logic_vector(31 downto 0);
        awlen_0         : in     vl_logic_vector(7 downto 0);
        awsize_0        : in     vl_logic_vector(2 downto 0);
        awburst_0       : in     vl_logic_vector(1 downto 0);
        awlock_0        : in     vl_logic;
        awvalid_0       : in     vl_logic;
        awready_0       : out    vl_logic;
        awurgent_0      : in     vl_logic;
        awpoison_0      : in     vl_logic;
        wdata_0         : in     vl_logic_vector(127 downto 0);
        wstrb_0         : in     vl_logic_vector(15 downto 0);
        wlast_0         : in     vl_logic;
        wvalid_0        : in     vl_logic;
        wready_0        : out    vl_logic;
        bid_0           : out    vl_logic_vector(7 downto 0);
        bresp_0         : out    vl_logic_vector(1 downto 0);
        bvalid_0        : out    vl_logic;
        bready_0        : in     vl_logic;
        arid_0          : in     vl_logic_vector(7 downto 0);
        araddr_0        : in     vl_logic_vector(31 downto 0);
        arlen_0         : in     vl_logic_vector(7 downto 0);
        arsize_0        : in     vl_logic_vector(2 downto 0);
        arburst_0       : in     vl_logic_vector(1 downto 0);
        arlock_0        : in     vl_logic;
        arvalid_0       : in     vl_logic;
        arready_0       : out    vl_logic;
        arpoison_0      : in     vl_logic;
        rid_0           : out    vl_logic_vector(7 downto 0);
        rdata_0         : out    vl_logic_vector(127 downto 0);
        rresp_0         : out    vl_logic_vector(1 downto 0);
        rlast_0         : out    vl_logic;
        rvalid_0        : out    vl_logic;
        rready_0        : in     vl_logic;
        arurgent_0      : in     vl_logic;
        raq_push_0      : out    vl_logic;
        raq_split_0     : out    vl_logic;
        waq_push_0      : out    vl_logic;
        waq_split_0     : out    vl_logic;
        areset_1        : in     vl_logic;
        aclk_1          : in     vl_logic;
        awid_1          : in     vl_logic_vector(7 downto 0);
        awaddr_1        : in     vl_logic_vector(31 downto 0);
        awlen_1         : in     vl_logic_vector(7 downto 0);
        awsize_1        : in     vl_logic_vector(2 downto 0);
        awburst_1       : in     vl_logic_vector(1 downto 0);
        awlock_1        : in     vl_logic;
        awvalid_1       : in     vl_logic;
        awready_1       : out    vl_logic;
        awurgent_1      : in     vl_logic;
        awpoison_1      : in     vl_logic;
        wdata_1         : in     vl_logic_vector(63 downto 0);
        wstrb_1         : in     vl_logic_vector(7 downto 0);
        wlast_1         : in     vl_logic;
        wvalid_1        : in     vl_logic;
        wready_1        : out    vl_logic;
        bid_1           : out    vl_logic_vector(7 downto 0);
        bresp_1         : out    vl_logic_vector(1 downto 0);
        bvalid_1        : out    vl_logic;
        bready_1        : in     vl_logic;
        arid_1          : in     vl_logic_vector(7 downto 0);
        araddr_1        : in     vl_logic_vector(31 downto 0);
        arlen_1         : in     vl_logic_vector(7 downto 0);
        arsize_1        : in     vl_logic_vector(2 downto 0);
        arburst_1       : in     vl_logic_vector(1 downto 0);
        arlock_1        : in     vl_logic;
        arvalid_1       : in     vl_logic;
        arready_1       : out    vl_logic;
        arpoison_1      : in     vl_logic;
        rid_1           : out    vl_logic_vector(7 downto 0);
        rdata_1         : out    vl_logic_vector(63 downto 0);
        rresp_1         : out    vl_logic_vector(1 downto 0);
        rlast_1         : out    vl_logic;
        rvalid_1        : out    vl_logic;
        rready_1        : in     vl_logic;
        arurgent_1      : in     vl_logic;
        raq_push_1      : out    vl_logic;
        raq_split_1     : out    vl_logic;
        waq_push_1      : out    vl_logic;
        waq_split_1     : out    vl_logic;
        areset_2        : in     vl_logic;
        aclk_2          : in     vl_logic;
        awid_2          : in     vl_logic_vector(7 downto 0);
        awaddr_2        : in     vl_logic_vector(31 downto 0);
        awlen_2         : in     vl_logic_vector(7 downto 0);
        awsize_2        : in     vl_logic_vector(2 downto 0);
        awburst_2       : in     vl_logic_vector(1 downto 0);
        awlock_2        : in     vl_logic;
        awvalid_2       : in     vl_logic;
        awready_2       : out    vl_logic;
        awurgent_2      : in     vl_logic;
        awpoison_2      : in     vl_logic;
        wdata_2         : in     vl_logic_vector(63 downto 0);
        wstrb_2         : in     vl_logic_vector(7 downto 0);
        wlast_2         : in     vl_logic;
        wvalid_2        : in     vl_logic;
        wready_2        : out    vl_logic;
        bid_2           : out    vl_logic_vector(7 downto 0);
        bresp_2         : out    vl_logic_vector(1 downto 0);
        bvalid_2        : out    vl_logic;
        bready_2        : in     vl_logic;
        arid_2          : in     vl_logic_vector(7 downto 0);
        araddr_2        : in     vl_logic_vector(31 downto 0);
        arlen_2         : in     vl_logic_vector(7 downto 0);
        arsize_2        : in     vl_logic_vector(2 downto 0);
        arburst_2       : in     vl_logic_vector(1 downto 0);
        arlock_2        : in     vl_logic;
        arvalid_2       : in     vl_logic;
        arready_2       : out    vl_logic;
        arpoison_2      : in     vl_logic;
        rid_2           : out    vl_logic_vector(7 downto 0);
        rdata_2         : out    vl_logic_vector(63 downto 0);
        rresp_2         : out    vl_logic_vector(1 downto 0);
        rlast_2         : out    vl_logic;
        rvalid_2        : out    vl_logic;
        rready_2        : in     vl_logic;
        arurgent_2      : in     vl_logic;
        raq_push_2      : out    vl_logic;
        raq_split_2     : out    vl_logic;
        waq_push_2      : out    vl_logic;
        waq_split_2     : out    vl_logic;
        awqos_0         : in     vl_logic_vector(3 downto 0);
        arqos_0         : in     vl_logic_vector(3 downto 0);
        awqos_1         : in     vl_logic_vector(3 downto 0);
        arqos_1         : in     vl_logic_vector(3 downto 0);
        awqos_2         : in     vl_logic_vector(3 downto 0);
        arqos_2         : in     vl_logic_vector(3 downto 0);
        csysreq_0       : in     vl_logic;
        csysack_0       : out    vl_logic;
        cactive_0       : out    vl_logic;
        csysreq_1       : in     vl_logic;
        csysack_1       : out    vl_logic;
        cactive_1       : out    vl_logic;
        csysreq_2       : in     vl_logic;
        csysack_2       : out    vl_logic;
        cactive_2       : out    vl_logic;
        csysreq_ddrc    : in     vl_logic;
        csysack_ddrc    : out    vl_logic;
        cactive_ddrc    : out    vl_logic;
        pa_rmask        : in     vl_logic_vector(2 downto 0);
        pa_wmask        : in     vl_logic_vector(2 downto 0);
        dfi_error       : in     vl_logic;
        dfi_error_info  : in     vl_logic_vector(2 downto 0);
        dfi_rddata      : in     vl_logic_vector(63 downto 0);
        dfi_rddata_valid: in     vl_logic_vector(3 downto 0);
        dfi_ctrlupd_ack : in     vl_logic;
        dfi_phyupd_req  : in     vl_logic;
        dfi_phyupd_type : in     vl_logic_vector(1 downto 0);
        dfi_lp_ack      : in     vl_logic;
        dfi_init_complete: in     vl_logic;
        dfi_address     : out    vl_logic_vector(31 downto 0);
        dfi_bank        : out    vl_logic_vector(5 downto 0);
        dfi_cas_n       : out    vl_logic_vector(1 downto 0);
        dfi_ras_n       : out    vl_logic_vector(1 downto 0);
        dfi_we_n        : out    vl_logic_vector(1 downto 0);
        dfi_cke         : out    vl_logic_vector(1 downto 0);
        dfi_cs          : out    vl_logic_vector(1 downto 0);
        dfi_odt         : out    vl_logic_vector(1 downto 0);
        dfi_reset_n     : out    vl_logic_vector(1 downto 0);
        dfi_wrdata      : out    vl_logic_vector(63 downto 0);
        dfi_wrdata_mask : out    vl_logic_vector(7 downto 0);
        dfi_wrdata_en   : out    vl_logic_vector(3 downto 0);
        dfi_rddata_en   : out    vl_logic_vector(3 downto 0);
        dfi_ctrlupd_req : out    vl_logic;
        dfi_dram_clk_disable: out    vl_logic;
        dfi_init_start  : out    vl_logic;
        dfi_frequency   : out    vl_logic_vector(4 downto 0);
        dfi_phyupd_ack  : out    vl_logic;
        dfi_lp_req      : out    vl_logic;
        dfi_lp_wakeup   : out    vl_logic_vector(3 downto 0);
        ddrc_preset     : out    vl_logic;
        ddrc_paddr      : out    vl_logic_vector(11 downto 0);
        ddrc_pwdata     : out    vl_logic_vector(31 downto 0);
        ddrc_pwrite     : out    vl_logic;
        ddrc_penable    : out    vl_logic;
        pclk            : in     vl_logic;
        preset          : in     vl_logic;
        paddr           : in     vl_logic_vector(11 downto 0);
        pwdata          : in     vl_logic_vector(31 downto 0);
        pwrite          : in     vl_logic;
        penable         : in     vl_logic;
        pslverr         : out    vl_logic;
        psel            : in     vl_logic;
        pready          : out    vl_logic;
        prdata          : out    vl_logic_vector(31 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of TRFC_MIN : constant is 2;
    attribute mti_svvh_generic_type of TREFI : constant is 2;
    attribute mti_svvh_generic_type of T_MRD : constant is 2;
    attribute mti_svvh_generic_type of T_MOD : constant is 2;
    attribute mti_svvh_generic_type of DDR_TYPE : constant is 1;
    attribute mti_svvh_generic_type of MR : constant is 2;
    attribute mti_svvh_generic_type of EMR : constant is 2;
    attribute mti_svvh_generic_type of EMR2 : constant is 2;
    attribute mti_svvh_generic_type of EMR3 : constant is 2;
    attribute mti_svvh_generic_type of WR2PRE : constant is 2;
    attribute mti_svvh_generic_type of T_FAW : constant is 2;
    attribute mti_svvh_generic_type of T_RAS_MAX : constant is 2;
    attribute mti_svvh_generic_type of T_RAS_MIN : constant is 2;
    attribute mti_svvh_generic_type of T_XP : constant is 2;
    attribute mti_svvh_generic_type of RD2PRE : constant is 2;
    attribute mti_svvh_generic_type of T_RC : constant is 2;
    attribute mti_svvh_generic_type of WL : constant is 2;
    attribute mti_svvh_generic_type of RL : constant is 2;
    attribute mti_svvh_generic_type of RD2WR : constant is 2;
    attribute mti_svvh_generic_type of WR2RD : constant is 2;
    attribute mti_svvh_generic_type of T_RCD : constant is 2;
    attribute mti_svvh_generic_type of T_CCD : constant is 2;
    attribute mti_svvh_generic_type of T_RRD : constant is 2;
    attribute mti_svvh_generic_type of T_RP : constant is 2;
    attribute mti_svvh_generic_type of T_CKSRX : constant is 2;
    attribute mti_svvh_generic_type of T_CKSRE : constant is 2;
    attribute mti_svvh_generic_type of T_CKESR : constant is 2;
    attribute mti_svvh_generic_type of T_CKE : constant is 2;
    attribute mti_svvh_generic_type of DFI_T_RDDATA_EN : constant is 2;
    attribute mti_svvh_generic_type of DFI_TPHY_WRLAT : constant is 2;
    attribute mti_svvh_generic_type of DATA_BUS_WIDTH : constant is 2;
    attribute mti_svvh_generic_type of ADDRESS_MAPPING_SEL : constant is 1;
    attribute mti_svvh_generic_type of MEM_ROW_ADDRESS : constant is 2;
    attribute mti_svvh_generic_type of MEM_COLUMN_ADDRESS : constant is 2;
    attribute mti_svvh_generic_type of MEM_BANK_ADDRESS : constant is 2;
end ipsl_hmic_h_ddrc_top_v1_1;
