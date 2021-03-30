library verilog;
use verilog.vl_types.all;
entity GTP_RAM16X4SP is
    generic(
        INIT_0          : vl_logic_vector(15 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        INIT_1          : vl_logic_vector(15 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        INIT_2          : vl_logic_vector(15 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        INIT_3          : vl_logic_vector(15 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0)
    );
    port(
        DO              : out    vl_logic_vector(3 downto 0);
        DI              : in     vl_logic_vector(3 downto 0);
        ADDR            : in     vl_logic_vector(3 downto 0);
        WCLK            : in     vl_logic;
        WE              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of INIT_0 : constant is 2;
    attribute mti_svvh_generic_type of INIT_1 : constant is 2;
    attribute mti_svvh_generic_type of INIT_2 : constant is 2;
    attribute mti_svvh_generic_type of INIT_3 : constant is 2;
end GTP_RAM16X4SP;
