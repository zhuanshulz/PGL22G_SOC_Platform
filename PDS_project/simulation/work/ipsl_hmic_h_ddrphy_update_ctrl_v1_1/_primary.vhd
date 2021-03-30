library verilog;
use verilog.vl_types.all;
entity ipsl_hmic_h_ddrphy_update_ctrl_v1_1 is
    generic(
        DATA_WIDTH      : string  := "16BIT"
    );
    port(
        rclk            : in     vl_logic;
        rst_n           : in     vl_logic;
        dll_update_n    : in     vl_logic;
        ddr_init_done   : in     vl_logic;
        dll_step_copy   : in     vl_logic_vector(7 downto 0);
        dqs_drift_l     : in     vl_logic_vector(1 downto 0);
        dqs_drift_h     : in     vl_logic_vector(1 downto 0);
        manual_update   : in     vl_logic;
        update_mask     : in     vl_logic_vector(2 downto 0);
        update_start    : out    vl_logic;
        ddrphy_update_type: out    vl_logic_vector(1 downto 0);
        ddrphy_update_comp_val_l: out    vl_logic_vector(1 downto 0);
        ddrphy_update_comp_dir_l: out    vl_logic;
        ddrphy_update_comp_val_h: out    vl_logic_vector(1 downto 0);
        ddrphy_update_comp_dir_h: out    vl_logic;
        ddrphy_update_done: in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of DATA_WIDTH : constant is 1;
end ipsl_hmic_h_ddrphy_update_ctrl_v1_1;
