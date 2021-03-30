library verilog;
use verilog.vl_types.all;
entity pgs_tsmac_apb_modify_v1_0 is
    port(
        hstcsn          : in     vl_logic;
        hstwrn          : in     vl_logic;
        hstable         : in     vl_logic;
        pwrt            : out    vl_logic;
        psel            : out    vl_logic
    );
end pgs_tsmac_apb_modify_v1_0;
