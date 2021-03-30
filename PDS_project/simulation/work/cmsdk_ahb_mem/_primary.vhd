library verilog;
use verilog.vl_types.all;
entity cmsdk_ahb_mem is
    port(
        HCLK            : in     vl_logic;
        HRESETn         : in     vl_logic;
        FCLK            : in     vl_logic;
        HSEL            : in     vl_logic;
        HREADY          : in     vl_logic;
        HTRANS          : in     vl_logic_vector(1 downto 0);
        HSIZE           : in     vl_logic_vector(2 downto 0);
        HWRITE          : in     vl_logic;
        HADDR           : in     vl_logic_vector(31 downto 0);
        HWDATA          : in     vl_logic_vector(31 downto 0);
        ECOREVNUM       : in     vl_logic_vector(3 downto 0);
        HREADYOUT       : out    vl_logic;
        HRESP           : out    vl_logic;
        HRDATA          : out    vl_logic_vector(31 downto 0);
        wdata           : out    vl_logic_vector(31 downto 0);
        waddr           : out    vl_logic_vector(21 downto 0);
        w_en            : out    vl_logic;
        rdata           : in     vl_logic_vector(31 downto 0);
        raddr           : out    vl_logic_vector(21 downto 0);
        r_en            : out    vl_logic;
        mem_cs          : out    vl_logic_vector(15 downto 0)
    );
end cmsdk_ahb_mem;
