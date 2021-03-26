library verilog;
use verilog.vl_types.all;
entity GTP_IGDES10 is
    generic(
        GRS_EN          : string  := "TRUE";
        LRS_EN          : string  := "TRUE";
        DPI_EN          : string  := "FALSE"
    );
    port(
        Q               : out    vl_logic_vector(9 downto 0);
        DPI_STS         : out    vl_logic_vector(1 downto 0);
        DPI_CTRL        : in     vl_logic_vector(1 downto 0);
        DPI_STS_CLR_N   : in     vl_logic;
        PADI            : in     vl_logic;
        DESCLK          : in     vl_logic;
        RCLK            : in     vl_logic;
        RST             : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of LRS_EN : constant is 1;
    attribute mti_svvh_generic_type of DPI_EN : constant is 1;
end GTP_IGDES10;
