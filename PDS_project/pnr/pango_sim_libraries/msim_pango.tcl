# ----------------------------------------
# Create compilation libraries
vlib usim
vmap usim "C:/Users/yangl/Documents/IC_competition/arm/M1_PGL22G_RTOS/PDS_project/pnr/pango_sim_libraries/usim"
vlib vsim
vmap vsim "C:/Users/yangl/Documents/IC_competition/arm/M1_PGL22G_RTOS/PDS_project/pnr/pango_sim_libraries/vsim"
#name lib path
set gtp_dir "C:/pango/PDS_2020.3-SP3.1-ads/arch/vendor/pango/verilog/simulation"
#compile library
vlog -incr $gtp_dir/*.v -work usim
cd "C:/pango/PDS_2020.3-SP3.1-ads/arch/vendor/pango/verilog/simulation/modelsim10.2c"
vmap usim "C:/Users/yangl/Documents/IC_competition/arm/M1_PGL22G_RTOS/PDS_project/pnr/pango_sim_libraries/usim"
vlog -incr -f ./filelist_adc_e2_gtp.f -work usim
vlog -incr -f ./filelist_adc_gtp.f -work usim
vlog -incr -f ./filelist_ddc_e2_gtp.f -work usim
vlog -incr -f ./filelist_ddrc_gtp.f -work usim -sv -mfcu
vlog -incr -f ./filelist_ddrphy_gtp.f -work usim
vlog -incr -f ./filelist_dll_e2_gtp.f -work usim
vlog -incr -f ./filelist_hsst_e2_gtp.f -work usim
vlog -incr -f ./filelist_hsst_gtp.f -work usim
vlog -incr -f ./filelist_hsstlp_lane_gtp.f -work usim
vlog -incr -f ./filelist_hsstlp_pll_gtp.f -work usim
vlog -incr -f ./filelist_iolhr_dft_gtp.f -work usim
vlog -incr -f ./filelist_ipal_e1_gtp.f -work usim
vlog -incr -f ./filelist_ipal_e2_gtp.f -work usim
vlog -incr -f ./filelist_iserdes_e2_gtp.f -work usim
vlog -incr -f ./filelist_oserdes_e2_gtp.f -work usim
vlog -incr -f ./filelist_pciegen2_gtp.f -work usim -sv -mfcu
vlog -incr -f ./filelist_pciegen3_gtp.f -work usim -sv -mfcu
vlog -incr ./*.vp -work usim
#name lib path
set fabv_dir "C:/pango/PDS_2020.3-SP3.1-ads/arch/vendor/pango/verilog/bsim"
#compile library
vlog -incr $fabv_dir/*.v -work vsim
cd "C:/pango/PDS_2020.3-SP3.1-ads/arch/vendor/pango/verilog/bsim/modelsim10.2c"
vmap vsim "C:/Users/yangl/Documents/IC_competition/arm/M1_PGL22G_RTOS/PDS_project/pnr/pango_sim_libraries/vsim"
vlog -incr -f ./filelist_adc_e2_gtp.f -work vsim
vlog -incr -f ./filelist_adc_gtp.f -work vsim
vlog -incr -f ./filelist_ddc_e2_gtp.f -work vsim
vlog -incr -f ./filelist_ddrc_gtp.f -work vsim -sv -mfcu
vlog -incr -f ./filelist_ddrphy_gtp.f -work vsim
vlog -incr -f ./filelist_dll_e2_gtp.f -work vsim
vlog -incr -f ./filelist_hsst_e2_gtp.f -work vsim
vlog -incr -f ./filelist_hsst_gtp.f -work vsim
vlog -incr -f ./filelist_hsstlp_lane_gtp.f -work vsim
vlog -incr -f ./filelist_hsstlp_pll_gtp.f -work vsim
vlog -incr -f ./filelist_iolhr_dft_gtp.f -work vsim
vlog -incr -f ./filelist_ipal_e1_gtp.f -work vsim
vlog -incr -f ./filelist_ipal_e2_gtp.f -work vsim
vlog -incr -f ./filelist_iserdes_e2_gtp.f -work vsim
vlog -incr -f ./filelist_oserdes_e2_gtp.f -work vsim
vlog -incr -f ./filelist_pciegen2_gtp.f -work vsim -sv -mfcu
vlog -incr -f ./filelist_pciegen3_gtp.f -work vsim -sv -mfcu
vlog -incr ./*.vp -work vsim
quit -force

# ----------------------------------------
