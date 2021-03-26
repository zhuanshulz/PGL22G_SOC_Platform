library verilog;
use verilog.vl_types.all;
entity V_ISERDES_E1 is
    generic(
        ISERDES_MODE    : string  := "IDES4";
        GRS_EN          : string  := "TRUE"
    );
    port(
        DO              : out    vl_logic_vector(7 downto 0);
        DIA             : in     vl_logic;
        DIC             : in     vl_logic;
        ICLKA           : in     vl_logic;
        ICLKC           : in     vl_logic;
        RCLKA           : in     vl_logic;
        RCLKC           : in     vl_logic;
        ALIGNWDA        : in     vl_logic;
        ALIGNWDC        : in     vl_logic;
        RSTA            : in     vl_logic;
        RSTC            : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of ISERDES_MODE : constant is 1;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
end V_ISERDES_E1;
