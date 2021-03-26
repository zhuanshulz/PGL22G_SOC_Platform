library verilog;
use verilog.vl_types.all;
entity APM_H_INST_CTRL is
    generic(
        SEL_CLK         : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        SEL_CE          : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        SEL_RST         : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        SYNC_RST        : vl_logic := Hi0
    );
    port(
        reg_clk         : out    vl_logic;
        reg_ce          : out    vl_logic;
        reg_arst        : out    vl_logic;
        reg_srst        : out    vl_logic;
        CLK             : in     vl_logic_vector(3 downto 0);
        CE              : in     vl_logic_vector(3 downto 0);
        RST             : in     vl_logic_vector(3 downto 0);
        GRS             : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of SEL_CLK : constant is 2;
    attribute mti_svvh_generic_type of SEL_CE : constant is 2;
    attribute mti_svvh_generic_type of SEL_RST : constant is 2;
    attribute mti_svvh_generic_type of SYNC_RST : constant is 1;
end APM_H_INST_CTRL;
