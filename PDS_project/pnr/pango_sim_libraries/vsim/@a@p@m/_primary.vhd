library verilog;
use verilog.vl_types.all;
entity APM is
    generic(
        GRS_EN          : string  := "TRUE";
        CLK_IR_0_XA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_IR_1_XA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_IR_2_YA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_IR_3_YA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_IR_4_ZA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_IR_5_ZA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_IR_6_ZA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_IR_7_XB     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_IR_8_XB     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_IR_9_YB     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_IR_10_YB    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_IR_11_ZB    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_IR_12_ZB    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_IR_13_ZB    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_0_XA      : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_1_XA      : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_2_YA      : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_3_YA      : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_4_ZA      : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_5_ZA      : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_6_ZA      : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_7_XB      : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_8_XB      : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_9_YB      : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_10_YB     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_11_ZB     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_12_ZB     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_IR_13_ZB     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_0_XA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_1_XA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_2_YA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_3_YA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_4_ZA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_5_ZA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_6_ZA     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_7_XB     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_8_XB     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_9_YB     : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_10_YB    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_11_ZB    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_12_ZB    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_IR_13_ZB    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        SYNC_IR_0_XA    : vl_logic := Hi0;
        SYNC_IR_1_XA    : vl_logic := Hi0;
        SYNC_IR_2_YA    : vl_logic := Hi0;
        SYNC_IR_3_YA    : vl_logic := Hi0;
        SYNC_IR_4_ZA    : vl_logic := Hi0;
        SYNC_IR_5_ZA    : vl_logic := Hi0;
        SYNC_IR_6_ZA    : vl_logic := Hi0;
        SYNC_IR_7_XB    : vl_logic := Hi0;
        SYNC_IR_8_XB    : vl_logic := Hi0;
        SYNC_IR_9_YB    : vl_logic := Hi0;
        SYNC_IR_10_YB   : vl_logic := Hi0;
        SYNC_IR_11_ZB   : vl_logic := Hi0;
        SYNC_IR_12_ZB   : vl_logic := Hi0;
        SYNC_IR_13_ZB   : vl_logic := Hi0;
        IR_BYP_0_XA     : vl_logic := Hi0;
        IR_BYP_1_XA     : vl_logic := Hi0;
        IR_BYP_2_YA     : vl_logic := Hi0;
        IR_BYP_3_YA     : vl_logic := Hi0;
        IR_BYP_4_ZA     : vl_logic := Hi0;
        IR_BYP_5_ZA     : vl_logic := Hi0;
        IR_BYP_6_ZA     : vl_logic := Hi0;
        IR_BYP_7_XB     : vl_logic := Hi0;
        IR_BYP_8_XB     : vl_logic := Hi0;
        IR_BYP_9_YB     : vl_logic := Hi0;
        IR_BYP_10_YB    : vl_logic := Hi0;
        IR_BYP_11_ZB    : vl_logic := Hi0;
        IR_BYP_12_ZB    : vl_logic := Hi0;
        IR_BYP_13_ZB    : vl_logic := Hi0;
        OPCD_BYP        : vl_logic_vector(8 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        CONST_IA0       : vl_logic_vector(18 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        CONST_IA1       : vl_logic_vector(18 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        SOURCEA         : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        SOURCEB         : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        SOURCEC         : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        IRDSEL_B        : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        IRDSEL_C        : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        DBYP_C          : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        DXIA_SIGNED_POL : vl_logic := Hi0;
        DYIA_SIGNED_POL : vl_logic := Hi0;
        DZIA_SIGNED_POL : vl_logic := Hi0;
        DXIB_SIGNED_POL : vl_logic := Hi0;
        DYIB_SIGNED_POL : vl_logic := Hi0;
        DZIB_SIGNED_POL : vl_logic := Hi0;
        OP_PRAD_A_POL   : vl_logic := Hi0;
        OP_PRAD_B_POL   : vl_logic := Hi0;
        OPCD            : vl_logic_vector(10 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        OPCD_DYN_SEL    : vl_logic_vector(10 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        OPCD_DYN_POL    : vl_logic_vector(10 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        CLK_CTIR        : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        CE_CTIR         : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        RST_CTIR        : vl_logic_vector(7 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        SYNC_CTIR       : vl_logic_vector(3 downto 0) := (Hi0, Hi0, Hi0, Hi0);
        CTRL_IRBYP      : vl_logic_vector(4 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0);
        IRSHF_B_SEL     : vl_logic := Hi0;
        CYSIGNED_SEL    : vl_logic := Hi0;
        IRSHF_C_SEL     : vl_logic := Hi0;
        CZSIGNED_SEL    : vl_logic := Hi0;
        SIGNED_ENA      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        SIGNED_ENB      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        SIGNED_ENC      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        DXIA_PSE        : vl_logic_vector(0 to 16) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        DYIA_PSE        : vl_logic_vector(0 to 16) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        DZIA_PSE        : integer := 0;
        DXIB_PSE        : vl_logic_vector(0 to 16) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        DYIB_PSE        : vl_logic_vector(0 to 16) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        DZIB_PSE        : vl_logic_vector(0 to 30) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        PRAD_EN         : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        PRAD26          : vl_logic := Hi0;
        CLK_PRAD_0_XA   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_PRAD_1_XA   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_PRAD_2_YA   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_PRAD_3_YA   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_PRAD_4_XB   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_PRAD_5_XB   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_PRAD_6_YB   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CLK_PRAD_7_YB   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_PRAD_0_XA    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_PRAD_1_XA    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_PRAD_2_YA    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_PRAD_3_YA    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_PRAD_4_XB    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_PRAD_5_XB    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_PRAD_6_YB    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CE_PRAD_7_YB    : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_PRAD_0_XA   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_PRAD_1_XA   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_PRAD_2_YA   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_PRAD_3_YA   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_PRAD_4_XB   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_PRAD_5_XB   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_PRAD_6_YB   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        RST_PRAD_7_YB   : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        SYNC_PRAD_0_XA  : vl_logic := Hi0;
        SYNC_PRAD_1_XA  : vl_logic := Hi0;
        SYNC_PRAD_2_YA  : vl_logic := Hi0;
        SYNC_PRAD_3_YA  : vl_logic := Hi0;
        SYNC_PRAD_4_XB  : vl_logic := Hi0;
        SYNC_PRAD_5_XB  : vl_logic := Hi0;
        SYNC_PRAD_6_YB  : vl_logic := Hi0;
        SYNC_PRAD_7_YB  : vl_logic := Hi0;
        PRADOR_BYP_0_XA : vl_logic := Hi0;
        PRADOR_BYP_1_XA : vl_logic := Hi0;
        PRADOR_BYP_2_YA : vl_logic := Hi0;
        PRADOR_BYP_3_YA : vl_logic := Hi0;
        PRADOR_BYP_4_XB : vl_logic := Hi0;
        PRADOR_BYP_5_XB : vl_logic := Hi0;
        PRADOR_BYP_6_YB : vl_logic := Hi0;
        PRADOR_BYP_7_YB : vl_logic := Hi0;
        CLK_PR_0_MA     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CLK_PR_1_MA     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CLK_PR_2_MB     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CLK_PR_3_MB     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CLK_PR_4_XA     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CLK_PR_5_XB     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CLK_PR_6_YA     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CLK_PR_7_YB     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CLK_PR_8_ZA     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CLK_PR_9_ZB     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_PR_0_MA      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_PR_1_MA      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_PR_2_MB      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_PR_3_MB      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_PR_4_XA      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_PR_5_XB      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_PR_6_YA      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_PR_7_YB      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_PR_8_ZA      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_PR_9_ZB      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_PR_0_MA     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_PR_1_MA     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_PR_2_MB     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_PR_3_MB     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_PR_4_XA     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_PR_5_XB     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_PR_6_YA     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_PR_7_YB     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_PR_8_ZA     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_PR_9_ZB     : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        SYNC_PR_0_MA    : vl_logic := Hi0;
        SYNC_PR_1_MA    : vl_logic := Hi0;
        SYNC_PR_2_MB    : vl_logic := Hi0;
        SYNC_PR_3_MB    : vl_logic := Hi0;
        SYNC_PR_4_XA    : vl_logic := Hi0;
        SYNC_PR_5_XB    : vl_logic := Hi0;
        SYNC_PR_6_YA    : vl_logic := Hi0;
        SYNC_PR_7_YB    : vl_logic := Hi0;
        SYNC_PR_8_ZA    : vl_logic := Hi0;
        SYNC_PR_9_ZB    : vl_logic := Hi0;
        PR_BYP_0_MA     : vl_logic := Hi0;
        PR_BYP_1_MA     : vl_logic := Hi0;
        PR_BYP_2_MB     : vl_logic := Hi0;
        PR_BYP_3_MB     : vl_logic := Hi0;
        PR_BYP_4_XA     : vl_logic := Hi0;
        PR_BYP_5_XB     : vl_logic := Hi0;
        PR_BYP_6_YA     : vl_logic := Hi0;
        PR_BYP_7_YB     : vl_logic := Hi0;
        PR_BYP_8_ZA     : vl_logic := Hi0;
        PR_BYP_9_ZB     : vl_logic := Hi0;
        M9_MODE         : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        M19_MODE        : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        M27_MODE        : vl_logic := Hi0;
        CLK_CTPR        : vl_logic_vector(3 downto 0) := (Hi0, Hi0, Hi0, Hi0);
        CE_CTPR         : vl_logic_vector(3 downto 0) := (Hi0, Hi0, Hi0, Hi0);
        RST_CTPR        : vl_logic_vector(3 downto 0) := (Hi0, Hi0, Hi0, Hi0);
        SYNC_CTPR       : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        CTRL_PRBYP      : vl_logic_vector(2 downto 0) := (Hi0, Hi0, Hi0);
        CLK_OR_3_B      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CLK_OR_2_B      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CLK_OR_1_A      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CLK_OR_0_A      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_OR_3_B       : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_OR_2_B       : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_OR_1_A       : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        CE_OR_0_A       : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_OR_3_B      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_OR_2_B      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_OR_1_A      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        RST_OR_0_A      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        SYNC_OR_3_B     : vl_logic := Hi0;
        SYNC_OR_2_B     : vl_logic := Hi0;
        SYNC_OR_1_A     : vl_logic := Hi0;
        SYNC_OR_0_A     : vl_logic := Hi0;
        OR_BYP_3_B      : vl_logic := Hi0;
        OR_BYP_2_B      : vl_logic := Hi0;
        OR_BYP_1_A      : vl_logic := Hi0;
        OR_BYP_0_A      : vl_logic := Hi0;
        RTI             : vl_logic_vector(0 to 63) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        SEL_SAB_CR27    : vl_logic := Hi0;
        SEL_SAB_CR59    : vl_logic := Hi0;
        FLAG_EN         : vl_logic := Hi0;
        CR64_SAB        : vl_logic := Hi0;
        SIGN_SELIR      : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        TERNARY         : vl_logic := Hi0;
        MASK01          : vl_logic_vector(0 to 64) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        MASKPAT         : vl_logic_vector(0 to 63) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        MCPAT           : vl_logic_vector(0 to 63) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        MASKPATSEL      : vl_logic := Hi0;
        MCPATSEL        : vl_logic := Hi0;
        CSIGN_EXT       : vl_logic := Hi0;
        CSIGN_PRE       : vl_logic := Hi0;
        SC_ALUEN        : vl_logic := Hi0;
        SEL_SYO         : vl_logic := Hi0;
        SEL_SZO         : vl_logic := Hi0;
        OR2CASCADE_EN   : vl_logic := Hi0
    );
    port(
        DXIA            : in     vl_logic_vector(17 downto 0);
        DXIA_SIGNED     : in     vl_logic;
        DYIA            : in     vl_logic_vector(17 downto 0);
        DYIA_SIGNED     : in     vl_logic;
        DXIB            : in     vl_logic_vector(17 downto 0);
        DXIB_SIGNED     : in     vl_logic;
        DYIB            : in     vl_logic_vector(17 downto 0);
        DYIB_SIGNED     : in     vl_logic;
        DZIA            : in     vl_logic_vector(31 downto 0);
        DZIA_SIGNED     : in     vl_logic;
        DZIB            : in     vl_logic_vector(31 downto 0);
        DZIB_SIGNED     : in     vl_logic;
        APM_OP_IR       : in     vl_logic_vector(8 downto 0);
        APM_OP_PRAD     : in     vl_logic_vector(1 downto 0);
        APM_OP_POST     : in     vl_logic_vector(10 downto 0);
        CYI             : in     vl_logic_vector(26 downto 0);
        CYI_SIGNED      : in     vl_logic;
        CZI             : in     vl_logic_vector(26 downto 0);
        CZI_SIGNED      : in     vl_logic;
        CPI             : in     vl_logic_vector(64 downto 0);
        CPI_SIGNED      : in     vl_logic;
        CLK             : in     vl_logic_vector(3 downto 0);
        CE              : in     vl_logic_vector(3 downto 0);
        RST             : in     vl_logic_vector(3 downto 0);
        CYO             : out    vl_logic_vector(26 downto 0);
        CYO_SIGNED      : out    vl_logic;
        CZO             : out    vl_logic_vector(26 downto 0);
        CZO_SIGNED      : out    vl_logic;
        CPO             : out    vl_logic_vector(64 downto 0);
        CPO_SIGNED      : out    vl_logic;
        DPO             : out    vl_logic_vector(73 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GRS_EN : constant is 1;
    attribute mti_svvh_generic_type of CLK_IR_0_XA : constant is 2;
    attribute mti_svvh_generic_type of CLK_IR_1_XA : constant is 2;
    attribute mti_svvh_generic_type of CLK_IR_2_YA : constant is 2;
    attribute mti_svvh_generic_type of CLK_IR_3_YA : constant is 2;
    attribute mti_svvh_generic_type of CLK_IR_4_ZA : constant is 2;
    attribute mti_svvh_generic_type of CLK_IR_5_ZA : constant is 2;
    attribute mti_svvh_generic_type of CLK_IR_6_ZA : constant is 2;
    attribute mti_svvh_generic_type of CLK_IR_7_XB : constant is 2;
    attribute mti_svvh_generic_type of CLK_IR_8_XB : constant is 2;
    attribute mti_svvh_generic_type of CLK_IR_9_YB : constant is 2;
    attribute mti_svvh_generic_type of CLK_IR_10_YB : constant is 2;
    attribute mti_svvh_generic_type of CLK_IR_11_ZB : constant is 2;
    attribute mti_svvh_generic_type of CLK_IR_12_ZB : constant is 2;
    attribute mti_svvh_generic_type of CLK_IR_13_ZB : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_0_XA : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_1_XA : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_2_YA : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_3_YA : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_4_ZA : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_5_ZA : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_6_ZA : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_7_XB : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_8_XB : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_9_YB : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_10_YB : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_11_ZB : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_12_ZB : constant is 2;
    attribute mti_svvh_generic_type of CE_IR_13_ZB : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_0_XA : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_1_XA : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_2_YA : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_3_YA : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_4_ZA : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_5_ZA : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_6_ZA : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_7_XB : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_8_XB : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_9_YB : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_10_YB : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_11_ZB : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_12_ZB : constant is 2;
    attribute mti_svvh_generic_type of RST_IR_13_ZB : constant is 2;
    attribute mti_svvh_generic_type of SYNC_IR_0_XA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_IR_1_XA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_IR_2_YA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_IR_3_YA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_IR_4_ZA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_IR_5_ZA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_IR_6_ZA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_IR_7_XB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_IR_8_XB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_IR_9_YB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_IR_10_YB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_IR_11_ZB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_IR_12_ZB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_IR_13_ZB : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_0_XA : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_1_XA : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_2_YA : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_3_YA : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_4_ZA : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_5_ZA : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_6_ZA : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_7_XB : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_8_XB : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_9_YB : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_10_YB : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_11_ZB : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_12_ZB : constant is 1;
    attribute mti_svvh_generic_type of IR_BYP_13_ZB : constant is 1;
    attribute mti_svvh_generic_type of OPCD_BYP : constant is 2;
    attribute mti_svvh_generic_type of CONST_IA0 : constant is 2;
    attribute mti_svvh_generic_type of CONST_IA1 : constant is 2;
    attribute mti_svvh_generic_type of SOURCEA : constant is 2;
    attribute mti_svvh_generic_type of SOURCEB : constant is 2;
    attribute mti_svvh_generic_type of SOURCEC : constant is 2;
    attribute mti_svvh_generic_type of IRDSEL_B : constant is 2;
    attribute mti_svvh_generic_type of IRDSEL_C : constant is 2;
    attribute mti_svvh_generic_type of DBYP_C : constant is 2;
    attribute mti_svvh_generic_type of DXIA_SIGNED_POL : constant is 1;
    attribute mti_svvh_generic_type of DYIA_SIGNED_POL : constant is 1;
    attribute mti_svvh_generic_type of DZIA_SIGNED_POL : constant is 1;
    attribute mti_svvh_generic_type of DXIB_SIGNED_POL : constant is 1;
    attribute mti_svvh_generic_type of DYIB_SIGNED_POL : constant is 1;
    attribute mti_svvh_generic_type of DZIB_SIGNED_POL : constant is 1;
    attribute mti_svvh_generic_type of OP_PRAD_A_POL : constant is 1;
    attribute mti_svvh_generic_type of OP_PRAD_B_POL : constant is 1;
    attribute mti_svvh_generic_type of OPCD : constant is 2;
    attribute mti_svvh_generic_type of OPCD_DYN_SEL : constant is 2;
    attribute mti_svvh_generic_type of OPCD_DYN_POL : constant is 2;
    attribute mti_svvh_generic_type of CLK_CTIR : constant is 2;
    attribute mti_svvh_generic_type of CE_CTIR : constant is 2;
    attribute mti_svvh_generic_type of RST_CTIR : constant is 2;
    attribute mti_svvh_generic_type of SYNC_CTIR : constant is 2;
    attribute mti_svvh_generic_type of CTRL_IRBYP : constant is 2;
    attribute mti_svvh_generic_type of IRSHF_B_SEL : constant is 1;
    attribute mti_svvh_generic_type of CYSIGNED_SEL : constant is 1;
    attribute mti_svvh_generic_type of IRSHF_C_SEL : constant is 1;
    attribute mti_svvh_generic_type of CZSIGNED_SEL : constant is 1;
    attribute mti_svvh_generic_type of SIGNED_ENA : constant is 1;
    attribute mti_svvh_generic_type of SIGNED_ENB : constant is 1;
    attribute mti_svvh_generic_type of SIGNED_ENC : constant is 1;
    attribute mti_svvh_generic_type of DXIA_PSE : constant is 1;
    attribute mti_svvh_generic_type of DYIA_PSE : constant is 1;
    attribute mti_svvh_generic_type of DZIA_PSE : constant is 1;
    attribute mti_svvh_generic_type of DXIB_PSE : constant is 1;
    attribute mti_svvh_generic_type of DYIB_PSE : constant is 1;
    attribute mti_svvh_generic_type of DZIB_PSE : constant is 1;
    attribute mti_svvh_generic_type of PRAD_EN : constant is 2;
    attribute mti_svvh_generic_type of PRAD26 : constant is 1;
    attribute mti_svvh_generic_type of CLK_PRAD_0_XA : constant is 2;
    attribute mti_svvh_generic_type of CLK_PRAD_1_XA : constant is 2;
    attribute mti_svvh_generic_type of CLK_PRAD_2_YA : constant is 2;
    attribute mti_svvh_generic_type of CLK_PRAD_3_YA : constant is 2;
    attribute mti_svvh_generic_type of CLK_PRAD_4_XB : constant is 2;
    attribute mti_svvh_generic_type of CLK_PRAD_5_XB : constant is 2;
    attribute mti_svvh_generic_type of CLK_PRAD_6_YB : constant is 2;
    attribute mti_svvh_generic_type of CLK_PRAD_7_YB : constant is 2;
    attribute mti_svvh_generic_type of CE_PRAD_0_XA : constant is 2;
    attribute mti_svvh_generic_type of CE_PRAD_1_XA : constant is 2;
    attribute mti_svvh_generic_type of CE_PRAD_2_YA : constant is 2;
    attribute mti_svvh_generic_type of CE_PRAD_3_YA : constant is 2;
    attribute mti_svvh_generic_type of CE_PRAD_4_XB : constant is 2;
    attribute mti_svvh_generic_type of CE_PRAD_5_XB : constant is 2;
    attribute mti_svvh_generic_type of CE_PRAD_6_YB : constant is 2;
    attribute mti_svvh_generic_type of CE_PRAD_7_YB : constant is 2;
    attribute mti_svvh_generic_type of RST_PRAD_0_XA : constant is 2;
    attribute mti_svvh_generic_type of RST_PRAD_1_XA : constant is 2;
    attribute mti_svvh_generic_type of RST_PRAD_2_YA : constant is 2;
    attribute mti_svvh_generic_type of RST_PRAD_3_YA : constant is 2;
    attribute mti_svvh_generic_type of RST_PRAD_4_XB : constant is 2;
    attribute mti_svvh_generic_type of RST_PRAD_5_XB : constant is 2;
    attribute mti_svvh_generic_type of RST_PRAD_6_YB : constant is 2;
    attribute mti_svvh_generic_type of RST_PRAD_7_YB : constant is 2;
    attribute mti_svvh_generic_type of SYNC_PRAD_0_XA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PRAD_1_XA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PRAD_2_YA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PRAD_3_YA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PRAD_4_XB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PRAD_5_XB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PRAD_6_YB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PRAD_7_YB : constant is 1;
    attribute mti_svvh_generic_type of PRADOR_BYP_0_XA : constant is 1;
    attribute mti_svvh_generic_type of PRADOR_BYP_1_XA : constant is 1;
    attribute mti_svvh_generic_type of PRADOR_BYP_2_YA : constant is 1;
    attribute mti_svvh_generic_type of PRADOR_BYP_3_YA : constant is 1;
    attribute mti_svvh_generic_type of PRADOR_BYP_4_XB : constant is 1;
    attribute mti_svvh_generic_type of PRADOR_BYP_5_XB : constant is 1;
    attribute mti_svvh_generic_type of PRADOR_BYP_6_YB : constant is 1;
    attribute mti_svvh_generic_type of PRADOR_BYP_7_YB : constant is 1;
    attribute mti_svvh_generic_type of CLK_PR_0_MA : constant is 1;
    attribute mti_svvh_generic_type of CLK_PR_1_MA : constant is 1;
    attribute mti_svvh_generic_type of CLK_PR_2_MB : constant is 1;
    attribute mti_svvh_generic_type of CLK_PR_3_MB : constant is 1;
    attribute mti_svvh_generic_type of CLK_PR_4_XA : constant is 1;
    attribute mti_svvh_generic_type of CLK_PR_5_XB : constant is 1;
    attribute mti_svvh_generic_type of CLK_PR_6_YA : constant is 1;
    attribute mti_svvh_generic_type of CLK_PR_7_YB : constant is 1;
    attribute mti_svvh_generic_type of CLK_PR_8_ZA : constant is 1;
    attribute mti_svvh_generic_type of CLK_PR_9_ZB : constant is 1;
    attribute mti_svvh_generic_type of CE_PR_0_MA : constant is 1;
    attribute mti_svvh_generic_type of CE_PR_1_MA : constant is 1;
    attribute mti_svvh_generic_type of CE_PR_2_MB : constant is 1;
    attribute mti_svvh_generic_type of CE_PR_3_MB : constant is 1;
    attribute mti_svvh_generic_type of CE_PR_4_XA : constant is 1;
    attribute mti_svvh_generic_type of CE_PR_5_XB : constant is 1;
    attribute mti_svvh_generic_type of CE_PR_6_YA : constant is 1;
    attribute mti_svvh_generic_type of CE_PR_7_YB : constant is 1;
    attribute mti_svvh_generic_type of CE_PR_8_ZA : constant is 1;
    attribute mti_svvh_generic_type of CE_PR_9_ZB : constant is 1;
    attribute mti_svvh_generic_type of RST_PR_0_MA : constant is 1;
    attribute mti_svvh_generic_type of RST_PR_1_MA : constant is 1;
    attribute mti_svvh_generic_type of RST_PR_2_MB : constant is 1;
    attribute mti_svvh_generic_type of RST_PR_3_MB : constant is 1;
    attribute mti_svvh_generic_type of RST_PR_4_XA : constant is 1;
    attribute mti_svvh_generic_type of RST_PR_5_XB : constant is 1;
    attribute mti_svvh_generic_type of RST_PR_6_YA : constant is 1;
    attribute mti_svvh_generic_type of RST_PR_7_YB : constant is 1;
    attribute mti_svvh_generic_type of RST_PR_8_ZA : constant is 1;
    attribute mti_svvh_generic_type of RST_PR_9_ZB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PR_0_MA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PR_1_MA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PR_2_MB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PR_3_MB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PR_4_XA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PR_5_XB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PR_6_YA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PR_7_YB : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PR_8_ZA : constant is 1;
    attribute mti_svvh_generic_type of SYNC_PR_9_ZB : constant is 1;
    attribute mti_svvh_generic_type of PR_BYP_0_MA : constant is 1;
    attribute mti_svvh_generic_type of PR_BYP_1_MA : constant is 1;
    attribute mti_svvh_generic_type of PR_BYP_2_MB : constant is 1;
    attribute mti_svvh_generic_type of PR_BYP_3_MB : constant is 1;
    attribute mti_svvh_generic_type of PR_BYP_4_XA : constant is 1;
    attribute mti_svvh_generic_type of PR_BYP_5_XB : constant is 1;
    attribute mti_svvh_generic_type of PR_BYP_6_YA : constant is 1;
    attribute mti_svvh_generic_type of PR_BYP_7_YB : constant is 1;
    attribute mti_svvh_generic_type of PR_BYP_8_ZA : constant is 1;
    attribute mti_svvh_generic_type of PR_BYP_9_ZB : constant is 1;
    attribute mti_svvh_generic_type of M9_MODE : constant is 2;
    attribute mti_svvh_generic_type of M19_MODE : constant is 2;
    attribute mti_svvh_generic_type of M27_MODE : constant is 1;
    attribute mti_svvh_generic_type of CLK_CTPR : constant is 2;
    attribute mti_svvh_generic_type of CE_CTPR : constant is 2;
    attribute mti_svvh_generic_type of RST_CTPR : constant is 2;
    attribute mti_svvh_generic_type of SYNC_CTPR : constant is 2;
    attribute mti_svvh_generic_type of CTRL_PRBYP : constant is 2;
    attribute mti_svvh_generic_type of CLK_OR_3_B : constant is 1;
    attribute mti_svvh_generic_type of CLK_OR_2_B : constant is 1;
    attribute mti_svvh_generic_type of CLK_OR_1_A : constant is 1;
    attribute mti_svvh_generic_type of CLK_OR_0_A : constant is 1;
    attribute mti_svvh_generic_type of CE_OR_3_B : constant is 1;
    attribute mti_svvh_generic_type of CE_OR_2_B : constant is 1;
    attribute mti_svvh_generic_type of CE_OR_1_A : constant is 1;
    attribute mti_svvh_generic_type of CE_OR_0_A : constant is 1;
    attribute mti_svvh_generic_type of RST_OR_3_B : constant is 1;
    attribute mti_svvh_generic_type of RST_OR_2_B : constant is 1;
    attribute mti_svvh_generic_type of RST_OR_1_A : constant is 1;
    attribute mti_svvh_generic_type of RST_OR_0_A : constant is 1;
    attribute mti_svvh_generic_type of SYNC_OR_3_B : constant is 1;
    attribute mti_svvh_generic_type of SYNC_OR_2_B : constant is 1;
    attribute mti_svvh_generic_type of SYNC_OR_1_A : constant is 1;
    attribute mti_svvh_generic_type of SYNC_OR_0_A : constant is 1;
    attribute mti_svvh_generic_type of OR_BYP_3_B : constant is 1;
    attribute mti_svvh_generic_type of OR_BYP_2_B : constant is 1;
    attribute mti_svvh_generic_type of OR_BYP_1_A : constant is 1;
    attribute mti_svvh_generic_type of OR_BYP_0_A : constant is 1;
    attribute mti_svvh_generic_type of RTI : constant is 1;
    attribute mti_svvh_generic_type of SEL_SAB_CR27 : constant is 1;
    attribute mti_svvh_generic_type of SEL_SAB_CR59 : constant is 1;
    attribute mti_svvh_generic_type of FLAG_EN : constant is 1;
    attribute mti_svvh_generic_type of CR64_SAB : constant is 1;
    attribute mti_svvh_generic_type of SIGN_SELIR : constant is 1;
    attribute mti_svvh_generic_type of TERNARY : constant is 1;
    attribute mti_svvh_generic_type of MASK01 : constant is 1;
    attribute mti_svvh_generic_type of MASKPAT : constant is 1;
    attribute mti_svvh_generic_type of MCPAT : constant is 1;
    attribute mti_svvh_generic_type of MASKPATSEL : constant is 1;
    attribute mti_svvh_generic_type of MCPATSEL : constant is 1;
    attribute mti_svvh_generic_type of CSIGN_EXT : constant is 1;
    attribute mti_svvh_generic_type of CSIGN_PRE : constant is 1;
    attribute mti_svvh_generic_type of SC_ALUEN : constant is 1;
    attribute mti_svvh_generic_type of SEL_SYO : constant is 1;
    attribute mti_svvh_generic_type of SEL_SZO : constant is 1;
    attribute mti_svvh_generic_type of OR2CASCADE_EN : constant is 1;
end APM;
