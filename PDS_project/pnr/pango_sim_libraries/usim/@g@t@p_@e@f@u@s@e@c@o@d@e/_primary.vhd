library verilog;
use verilog.vl_types.all;
entity GTP_EFUSECODE is
    generic(
        SIM_EFUSE_VALUE : vl_logic_vector(31 downto 0) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi0, Hi1, Hi0, Hi0, Hi0, Hi1, Hi1, Hi0, Hi1, Hi0, Hi0, Hi0, Hi1, Hi0, Hi1, Hi0, Hi1, Hi1, Hi0, Hi0, Hi1, Hi1, Hi1, Hi1, Hi0, Hi0, Hi0)
    );
    port(
        EFUSE_CODE      : out    vl_logic_vector(31 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of SIM_EFUSE_VALUE : constant is 2;
end GTP_EFUSECODE;
