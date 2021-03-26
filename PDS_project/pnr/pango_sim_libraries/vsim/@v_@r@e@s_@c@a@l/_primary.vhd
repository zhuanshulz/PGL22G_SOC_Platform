library verilog;
use verilog.vl_types.all;
entity V_RES_CAL is
    generic(
        BANK_LOC        : string  := "L0";
        CAL_CODE        : vl_logic_vector(19 downto 0) := (Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0);
        CAL_MODE        : string  := "STATIC_MODE";
        DDR_RES         : string  := "50"
    );
    port(
        CAL_DONE        : out    vl_logic;
        CAL_REQ         : in     vl_logic;
        USR_DRVN        : in     vl_logic_vector(4 downto 0);
        USR_DRVP        : in     vl_logic_vector(4 downto 0);
        USR_TERMN       : in     vl_logic_vector(4 downto 0);
        USR_TERMP       : in     vl_logic_vector(4 downto 0);
        NL              : out    vl_logic_vector(4 downto 0);
        PL              : out    vl_logic_vector(4 downto 0);
        TNL             : out    vl_logic_vector(4 downto 0);
        TPL             : out    vl_logic_vector(4 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of BANK_LOC : constant is 1;
    attribute mti_svvh_generic_type of CAL_CODE : constant is 2;
    attribute mti_svvh_generic_type of CAL_MODE : constant is 1;
    attribute mti_svvh_generic_type of DDR_RES : constant is 1;
end V_RES_CAL;
