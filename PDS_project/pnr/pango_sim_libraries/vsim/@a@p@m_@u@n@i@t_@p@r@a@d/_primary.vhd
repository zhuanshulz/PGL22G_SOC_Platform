library verilog;
use verilog.vl_types.all;
entity APM_UNIT_PRAD is
    generic(
        PRAD_EN         : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        PRAD8           : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        PRAD26          : vl_logic := Hi0;
        CLK_PRAD        : vl_logic_vector(15 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        CE_PRAD         : vl_logic_vector(15 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        RST_PRAD        : vl_logic_vector(15 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        SYNC_PRAD       : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        PRADOR_BYP      : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        GRS             : in     vl_logic;
        CLK             : in     vl_logic_vector(3 downto 0);
        CE              : in     vl_logic_vector(3 downto 0);
        RST             : in     vl_logic_vector(3 downto 0);
        xa              : in     vl_logic_vector(17 downto 0);
        xa_signed       : in     vl_logic;
        xb              : in     vl_logic_vector(17 downto 0);
        xb_signed       : in     vl_logic;
        zb              : in     vl_logic_vector(17 downto 0);
        zb_signed       : in     vl_logic;
        ya              : in     vl_logic_vector(17 downto 0);
        ya_signed       : in     vl_logic;
        yb              : in     vl_logic_vector(17 downto 0);
        yb_signed       : in     vl_logic;
        za              : in     vl_logic_vector(17 downto 0);
        za_signed       : in     vl_logic;
        prad_op         : in     vl_logic_vector(1 downto 0);
        preadd_xa       : out    vl_logic_vector(17 downto 0);
        preadd_xa_signed: out    vl_logic;
        preadd_ya       : out    vl_logic_vector(18 downto 0);
        preadd_ya_signed: out    vl_logic;
        preadd_za_signed: out    vl_logic;
        preadd_xb       : out    vl_logic_vector(17 downto 0);
        preadd_xb_signed: out    vl_logic;
        preadd_yb       : out    vl_logic_vector(18 downto 0);
        preadd_yb_signed: out    vl_logic;
        preadd_zb_signed: out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of PRAD_EN : constant is 2;
    attribute mti_svvh_generic_type of PRAD8 : constant is 1;
    attribute mti_svvh_generic_type of PRAD26 : constant is 1;
    attribute mti_svvh_generic_type of CLK_PRAD : constant is 2;
    attribute mti_svvh_generic_type of CE_PRAD : constant is 2;
    attribute mti_svvh_generic_type of RST_PRAD : constant is 2;
    attribute mti_svvh_generic_type of SYNC_PRAD : constant is 2;
    attribute mti_svvh_generic_type of PRADOR_BYP : constant is 2;
end APM_UNIT_PRAD;
