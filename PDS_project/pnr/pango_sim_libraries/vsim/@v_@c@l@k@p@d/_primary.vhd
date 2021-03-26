library verilog;
use verilog.vl_types.all;
entity V_CLKPD is
    port(
        FLAG_PD         : out    vl_logic;
        LOCK            : out    vl_logic;
        RST             : in     vl_logic;
        CLK_SAMPLE      : in     vl_logic;
        CLK_CTRL        : in     vl_logic;
        CLK_PHY         : in     vl_logic;
        DONE            : in     vl_logic
    );
end V_CLKPD;
