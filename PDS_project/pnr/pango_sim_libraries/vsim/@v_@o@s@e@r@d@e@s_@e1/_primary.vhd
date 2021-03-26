library verilog;
use verilog.vl_types.all;
entity V_OSERDES_E1 is
    generic(
        OSERDES_MODE    : string  := "OSER4";
        GRS_EN          : string  := "TRUE"
    );
    port(
        DOA             : out    vl_logic;
        DOC             : out    vl_logic;
        DI              : in     vl_logic_vector(7 downto 0);
        RCLKA           : in     vl_logic;
        RCLKC           : in     vl_logic;
        OCLKA           : in     vl_logic;
        OCLKC           : in     vl_logic;
        RSTA            : in     vl_logic;
        RSTC            : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of OSERDES_MODE : constant is 1;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
end V_OSERDES_E1;
