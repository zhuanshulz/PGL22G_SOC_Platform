library verilog;
use verilog.vl_types.all;
entity V_SCANCHAIN is
    generic(
        IDCODE          : vl_logic_vector(31 downto 0) := (Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1);
        CHAIN_NUM       : integer := 1
    );
    port(
        TCK             : in     vl_logic;
        TDI             : in     vl_logic;
        TMS             : in     vl_logic;
        TDO             : out    vl_logic;
        CAPDR           : out    vl_logic;
        JCLK            : out    vl_logic;
        RST             : out    vl_logic;
        FLG_USER        : out    vl_logic;
        SHFTDR          : out    vl_logic;
        TDI_USER        : out    vl_logic;
        UPDR            : out    vl_logic;
        TDO_USER        : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of IDCODE : constant is 2;
    attribute mti_svvh_generic_type of CHAIN_NUM : constant is 1;
end V_SCANCHAIN;
