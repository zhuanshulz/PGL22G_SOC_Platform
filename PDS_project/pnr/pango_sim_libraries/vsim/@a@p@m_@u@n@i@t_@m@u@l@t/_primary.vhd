library verilog;
use verilog.vl_types.all;
entity APM_UNIT_MULT is
    generic(
        CLK_PR          : vl_logic_vector(19 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        CE_PR           : vl_logic_vector(19 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        RST_PR          : vl_logic_vector(19 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        SYNC_PR         : vl_logic_vector(9 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        CLK_CTPR        : vl_logic_vector(3 downto 0) := (Hi0, Hi0, Hi0, Hi0);
        CE_CTPR         : vl_logic_vector(3 downto 0) := (Hi0, Hi0, Hi0, Hi0);
        RST_CTPR        : vl_logic_vector(3 downto 0) := (Hi0, Hi0, Hi0, Hi0);
        SYNC_CTPR       : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CTRL_PRBYP      : vl_logic_vector(2 downto 0) := (Hi0, Hi0, Hi0);
        M9_MODE         : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        M19_MODE        : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        M27_MODE        : vl_logic := Hi0;
        PR_BYP          : vl_logic_vector(0 to 9) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        GRS             : in     vl_logic;
        CLK             : in     vl_logic_vector(3 downto 0);
        CE              : in     vl_logic_vector(3 downto 0);
        RST             : in     vl_logic_vector(3 downto 0);
        preadd_xa       : in     vl_logic_vector(17 downto 0);
        preadd_xb       : in     vl_logic_vector(17 downto 0);
        preadd_ya       : in     vl_logic_vector(18 downto 0);
        preadd_yb       : in     vl_logic_vector(18 downto 0);
        post_op_ir      : in     vl_logic_vector(10 downto 0);
        asign_ext1      : in     vl_logic_vector(1 downto 0);
        bsign_ext1      : in     vl_logic_vector(1 downto 0);
        csign_ext1      : in     vl_logic_vector(1 downto 0);
        post_op_pr      : out    vl_logic_vector(10 downto 0);
        mult_a          : out    vl_logic_vector(45 downto 0);
        mult_b          : out    vl_logic_vector(36 downto 0);
        asign_ext2      : out    vl_logic_vector(1 downto 0);
        bsign_ext2      : out    vl_logic_vector(1 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of CLK_PR : constant is 2;
    attribute mti_svvh_generic_type of CE_PR : constant is 2;
    attribute mti_svvh_generic_type of RST_PR : constant is 2;
    attribute mti_svvh_generic_type of SYNC_PR : constant is 2;
    attribute mti_svvh_generic_type of CLK_CTPR : constant is 2;
    attribute mti_svvh_generic_type of CE_CTPR : constant is 2;
    attribute mti_svvh_generic_type of RST_CTPR : constant is 2;
    attribute mti_svvh_generic_type of SYNC_CTPR : constant is 2;
    attribute mti_svvh_generic_type of CTRL_PRBYP : constant is 2;
    attribute mti_svvh_generic_type of M9_MODE : constant is 1;
    attribute mti_svvh_generic_type of M19_MODE : constant is 1;
    attribute mti_svvh_generic_type of M27_MODE : constant is 1;
    attribute mti_svvh_generic_type of PR_BYP : constant is 1;
end APM_UNIT_MULT;
