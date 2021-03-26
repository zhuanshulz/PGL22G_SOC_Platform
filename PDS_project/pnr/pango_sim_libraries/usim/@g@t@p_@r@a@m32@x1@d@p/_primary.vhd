library verilog;
use verilog.vl_types.all;
entity GTP_RAM32X1DP is
    generic(
        INIT            : vl_logic_vector(31 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        DO              : out    vl_logic;
        DI              : in     vl_logic;
        RADDR           : in     vl_logic_vector(4 downto 0);
        WADDR           : in     vl_logic_vector(4 downto 0);
        WCLK            : in     vl_logic;
        WE              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of INIT : constant is 2;
end GTP_RAM32X1DP;
