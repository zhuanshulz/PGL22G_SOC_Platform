library verilog;
use verilog.vl_types.all;
entity axi1_wr_test is
    port(
        rstn            : in     vl_logic;
        clk             : in     vl_logic;
        awaddr_1        : out    vl_logic_vector(31 downto 0);
        awvalid_1       : out    vl_logic;
        awready_1       : in     vl_logic;
        wdata_1         : out    vl_logic_vector(63 downto 0);
        wlast_1         : out    vl_logic;
        wvalid_1        : out    vl_logic;
        wready_1        : in     vl_logic;
        araddr_1        : out    vl_logic_vector(31 downto 0);
        arvalid_1       : out    vl_logic;
        arready_1       : in     vl_logic;
        rdata_1         : in     vl_logic_vector(63 downto 0);
        rlast_1         : in     vl_logic;
        rvalid_1        : in     vl_logic;
        rready_1        : out    vl_logic
    );
end axi1_wr_test;
