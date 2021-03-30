library verilog;
use verilog.vl_types.all;
entity ex_data_fifo is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        wr_en           : in     vl_logic;
        wr_data         : in     vl_logic_vector(7 downto 0);
        wr_full         : out    vl_logic;
        rd_en           : in     vl_logic;
        rd_data         : out    vl_logic_vector(7 downto 0);
        almost_full     : out    vl_logic;
        rd_empty        : out    vl_logic;
        almost_empty    : out    vl_logic
    );
end ex_data_fifo;
