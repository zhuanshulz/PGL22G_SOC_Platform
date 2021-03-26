library verilog;
use verilog.vl_types.all;
entity V_RAM32X2 is
    generic(
        INIT0           : vl_logic_vector(31 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        INIT1           : vl_logic_vector(31 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        WE_POL          : string  := "FALSE"
    );
    port(
        RDO             : out    vl_logic_vector(1 downto 0);
        WDI             : in     vl_logic_vector(1 downto 0);
        RADDR           : in     vl_logic_vector(4 downto 0);
        WADDR           : in     vl_logic_vector(4 downto 0);
        WCLK            : in     vl_logic;
        WE              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of INIT0 : constant is 2;
    attribute mti_svvh_generic_type of INIT1 : constant is 2;
    attribute mti_svvh_generic_type of WE_POL : constant is 1;
end V_RAM32X2;
