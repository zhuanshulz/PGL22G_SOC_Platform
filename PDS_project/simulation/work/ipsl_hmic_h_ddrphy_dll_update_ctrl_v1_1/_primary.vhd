library verilog;
use verilog.vl_types.all;
entity ipsl_hmic_h_ddrphy_dll_update_ctrl_v1_1 is
    port(
        rclk            : in     vl_logic;
        rst_n           : in     vl_logic;
        dll_update_req_rst_ctrl: in     vl_logic;
        dll_update_ack_rst_ctrl: out    vl_logic;
        dll_update_req_training: in     vl_logic;
        dll_update_ack_training: out    vl_logic;
        dll_update_iorst_req: out    vl_logic;
        dll_update_iorst_ack: in     vl_logic;
        dll_update_n    : out    vl_logic
    );
end ipsl_hmic_h_ddrphy_dll_update_ctrl_v1_1;
