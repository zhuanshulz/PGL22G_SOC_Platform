library verilog;
use verilog.vl_types.all;
entity sd_card_sec_read_write is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        sd_init_done    : out    vl_logic;
        sd_sec_read     : in     vl_logic;
        sd_sec_read_addr: in     vl_logic_vector(31 downto 0);
        sd_sec_read_data: out    vl_logic_vector(7 downto 0);
        sd_sec_read_data_valid: out    vl_logic;
        sd_sec_read_end : out    vl_logic;
        sd_sec_write    : in     vl_logic;
        sd_sec_write_addr: in     vl_logic_vector(31 downto 0);
        sd_sec_write_data: in     vl_logic_vector(31 downto 0);
        sd_sec_write_data_req: out    vl_logic;
        sd_sec_write_end: out    vl_logic;
        spi_clk_div     : out    vl_logic_vector(15 downto 0);
        cmd_req         : out    vl_logic;
        cmd_req_ack     : in     vl_logic;
        cmd_req_error   : in     vl_logic;
        cmd             : out    vl_logic_vector(47 downto 0);
        cmd_r1          : out    vl_logic_vector(7 downto 0);
        cmd_data_len    : out    vl_logic_vector(15 downto 0);
        block_read_req  : out    vl_logic;
        block_read_valid: in     vl_logic;
        block_read_data : in     vl_logic_vector(7 downto 0);
        block_read_req_ack: in     vl_logic;
        block_write_req : out    vl_logic;
        block_write_data: out    vl_logic_vector(31 downto 0);
        block_write_data_rd: in     vl_logic;
        block_write_req_ack: in     vl_logic;
        SPI_LOW_SPEED_DIV: in     vl_logic_vector(15 downto 0);
        SPI_HIGH_SPEED_DIV: in     vl_logic_vector(15 downto 0);
        run_state       : out    vl_logic_vector(4 downto 0)
    );
end sd_card_sec_read_write;
