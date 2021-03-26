library verilog;
use verilog.vl_types.all;
entity V_ISERDES is
    generic(
        ISERDES_MODE    : string  := "IDDR";
        GRS_EN          : string  := "TRUE";
        LRS_EN          : string  := "TRUE"
    );
    port(
        DI              : in     vl_logic;
        ICLK            : in     vl_logic;
        DESCLK          : in     vl_logic;
        RCLK            : in     vl_logic;
        WADDR           : in     vl_logic_vector(2 downto 0);
        RADDR           : in     vl_logic_vector(2 downto 0);
        RST             : in     vl_logic;
        DO              : out    vl_logic_vector(7 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of ISERDES_MODE : constant is 1;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of LRS_EN : constant is 1;
end V_ISERDES;
