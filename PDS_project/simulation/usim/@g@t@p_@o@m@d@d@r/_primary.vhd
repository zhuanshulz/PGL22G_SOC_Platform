library verilog;
use verilog.vl_types.all;
entity GTP_OMDDR is
    generic(
        GRS_EN          : string  := "TRUE";
        LRS_EN          : string  := "TRUE"
    );
    port(
        PADO            : out    vl_logic;
        PADT            : out    vl_logic;
        D               : in     vl_logic_vector(1 downto 0);
        T               : in     vl_logic;
        RCLK            : in     vl_logic;
        OCLK            : in     vl_logic;
        RST             : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of LRS_EN : constant is 1;
end GTP_OMDDR;
