library verilog;
use verilog.vl_types.all;
entity pgs_tsmac_apb_port_v1_0 is
    generic(
        TP              : integer := 1
    );
    port(
        hstrst          : in     vl_logic;
        hstclk          : in     vl_logic;
        hstcsn          : in     vl_logic;
        hstwrn          : in     vl_logic;
        hstadx          : in     vl_logic_vector(7 downto 0);
        hstidat         : in     vl_logic_vector(31 downto 0);
        packet_cnt      : in     vl_logic_vector(63 downto 0);
        crc_err_cnt     : in     vl_logic_vector(63 downto 0);
        pause_ctr_cnt   : in     vl_logic_vector(63 downto 0);
        addr_err_cnt    : in     vl_logic_vector(63 downto 0);
        len_err_cnt     : in     vl_logic_vector(63 downto 0);
        frame_trc_cnt   : in     vl_logic_vector(63 downto 0);
        ifg_sma_cnt     : in     vl_logic_vector(63 downto 0);
        bcad_cnt        : in     vl_logic_vector(63 downto 0);
        mcad_cnt        : in     vl_logic_vector(63 downto 0);
        ucad_cnt        : in     vl_logic_vector(63 downto 0);
        hstoe           : out    vl_logic;
        hstodat         : out    vl_logic_vector(31 downto 0);
        dahash          : out    vl_logic_vector(8 downto 0);
        ppad            : out    vl_logic;
        pcrc            : out    vl_logic;
        phug            : out    vl_logic;
        povr            : out    vl_logic;
        fbc             : out    vl_logic;
        fuc             : out    vl_logic;
        fmc             : out    vl_logic;
        nfcs            : out    vl_logic;
        dmac            : out    vl_logic_vector(47 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of TP : constant is 1;
end pgs_tsmac_apb_port_v1_0;
