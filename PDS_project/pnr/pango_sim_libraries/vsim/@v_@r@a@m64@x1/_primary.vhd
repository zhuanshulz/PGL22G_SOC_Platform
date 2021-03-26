library verilog;
use verilog.vl_types.all;
entity V_RAM64X1 is
    generic(
        INIT            : vl_logic_vector(63 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        CS_MASK         : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        WE_POL          : string  := "FALSE"
    );
    port(
        RDO             : out    vl_logic;
        WDI             : in     vl_logic;
        CS              : in     vl_logic_vector(1 downto 0);
        WADDR           : in     vl_logic_vector(5 downto 0);
        RADDR           : in     vl_logic_vector(5 downto 0);
        WCLK            : in     vl_logic;
        WE              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of INIT : constant is 2;
    attribute mti_svvh_generic_type of CS_MASK : constant is 2;
    attribute mti_svvh_generic_type of WE_POL : constant is 1;
end V_RAM64X1;
