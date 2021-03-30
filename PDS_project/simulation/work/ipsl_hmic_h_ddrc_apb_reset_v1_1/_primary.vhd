library verilog;
use verilog.vl_types.all;
entity ipsl_hmic_h_ddrc_apb_reset_v1_1 is
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
        presetn         : in     vl_logic;
        pclk            : in     vl_logic;
        pwdata          : out    vl_logic_vector(31 downto 0);
        pwrite          : out    vl_logic;
        penable         : out    vl_logic;
        psel            : out    vl_logic;
        paddr           : out    vl_logic_vector(11 downto 0);
        prdata          : in     vl_logic_vector(31 downto 0);
        pready          : in     vl_logic;
        ddrc_init_start : in     vl_logic;
        ddrc_init_done  : out    vl_logic
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
end ipsl_hmic_h_ddrc_apb_reset_v1_1;
