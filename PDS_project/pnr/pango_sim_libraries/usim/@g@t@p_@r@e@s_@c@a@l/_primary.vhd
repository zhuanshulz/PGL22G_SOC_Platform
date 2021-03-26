library verilog;
use verilog.vl_types.all;
entity GTP_RES_CAL is
    generic(
        BANK_LOC        : string  := "L0";
        CAL_CODE        : vl_logic_vector(19 downto 0) := (Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi1, Hi0, Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi0);
        CAL_MODE        : string  := "STATIC_MODE";
        DDR_RES         : string  := "50"
    );
    port(
        CAL_DONE        : out    vl_logic;
        CAL_REQ         : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of BANK_LOC : constant is 1;
    attribute mti_svvh_generic_type of CAL_CODE : constant is 2;
    attribute mti_svvh_generic_type of CAL_MODE : constant is 1;
    attribute mti_svvh_generic_type of DDR_RES : constant is 1;
end GTP_RES_CAL;
