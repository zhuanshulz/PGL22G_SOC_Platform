library verilog;
use verilog.vl_types.all;
entity INT_FIFO18K_MEM is
    generic(
        DATA_WIDTH      : integer := 2;
        ASIZE           : integer := 12
    );
    port(
        dout            : out    vl_logic_vector(35 downto 0);
        din             : in     vl_logic_vector(35 downto 0);
        waddr           : in     vl_logic_vector(13 downto 0);
        raddr           : in     vl_logic_vector(13 downto 0);
        wr_en           : in     vl_logic;
        wclk            : in     vl_logic;
        full            : in     vl_logic;
        rstr            : in     vl_logic;
        rd_en           : in     vl_logic;
        rclk            : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of DATA_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of ASIZE : constant is 1;
end INT_FIFO18K_MEM;
