library verilog;
use verilog.vl_types.all;
entity ipsl_hmic_h_ddrphy_reset_ctrl_v1_1 is
    port(
        top_rst_n       : in     vl_logic;
        clk             : in     vl_logic;
        dll_update_iorst_req: in     vl_logic;
        dll_update_iorst_ack: out    vl_logic;
        dll_lock        : in     vl_logic;
        pll_lock        : in     vl_logic;
        dll_update_req_rst_ctrl: out    vl_logic;
        dll_update_ack_rst_ctrl: in     vl_logic;
        srb_rst_dll     : out    vl_logic;
        srb_dll_freeze  : out    vl_logic;
        ddrphy_rst      : out    vl_logic;
        srb_iol_rst     : out    vl_logic;
        srb_dqs_rstn    : out    vl_logic;
        srb_ioclkdiv_rstn: out    vl_logic;
        global_reset_n  : out    vl_logic;
        led0_ddrphy_rst : out    vl_logic
    );
end ipsl_hmic_h_ddrphy_reset_ctrl_v1_1;
