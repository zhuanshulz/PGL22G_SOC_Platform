library verilog;
use verilog.vl_types.all;
entity V_JTAGIF is
    generic(
        USERCODE        : vl_logic_vector(31 downto 0) := (Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1);
        IDCODE          : integer := 1431677610
    );
    port(
        TDO             : out    vl_logic;
        TCK             : in     vl_logic;
        TMS             : in     vl_logic;
        TDI             : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of USERCODE : constant is 1;
    attribute mti_svvh_generic_type of IDCODE : constant is 1;
end V_JTAGIF;
