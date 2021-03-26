library verilog;
use verilog.vl_types.all;
entity V_IPAL is
    generic(
        DATA_WIDTH      : string  := "X8";
        IDCODE          : vl_logic_vector(31 downto 0) := (Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1);
        MEM_DEPTH       : integer := 1616
    );
    port(
        RST_N           : in     vl_logic;
        CLK             : in     vl_logic;
        DI              : in     vl_logic_vector(7 downto 0);
        CS_N            : in     vl_logic;
        RW_SEL          : in     vl_logic;
        DO              : out    vl_logic_vector(7 downto 0);
        BUSY            : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of DATA_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of IDCODE : constant is 2;
    attribute mti_svvh_generic_type of MEM_DEPTH : constant is 1;
end V_IPAL;
