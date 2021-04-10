onerror {resume}
quietly WaveActivateNextPane {} 0

add wave -noupdate /m1_test/uut/ex_clk_50m
add wave -noupdate /m1_test/uut/rst_key
add wave -noupdate /m1_test/uut/gpio_in0
add wave -noupdate /m1_test/uut/gpio_in1
add wave -noupdate /m1_test/uut/LED
add wave -noupdate /m1_test/uut/RX
add wave -noupdate /m1_test/uut/TX

add wave -noupdate /m1_test/uut/HCLK


add wave -noupdate /m1_test/uut/mem_cs
add wave -noupdate /m1_test/uut/r_en
add wave -noupdate /m1_test/uut/raddr
add wave -noupdate /m1_test/uut/rdata1

add wave -noupdate /m1_test/uut/HSEL
add wave -noupdate /m1_test/uut/HTRANS
add wave -noupdate /m1_test/uut/HBURST
add wave -noupdate /m1_test/uut/mem_cs
add wave -noupdate /m1_test/uut/HSEL
add wave -noupdate /m1_test/uut/HSIZE
add wave -noupdate /m1_test/uut/HMASTLOCK
add wave -noupdate /m1_test/uut/HADDR
add wave -noupdate /m1_test/uut/HWDATA
add wave -noupdate /m1_test/uut/HREADY
add wave -noupdate /m1_test/uut/HREADYOUT_udp
add wave -noupdate /m1_test/uut/HRESP_udp
add wave -noupdate /m1_test/uut/HRDATA_udp
add wave -noupdate /m1_test/uut/HRDATAmux


TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {489852371880 fs} 0}
quietly wave cursor active 1
configure wave -namecolwidth 522
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits fs
update
WaveRestoreZoom {0 fs} {96695550 ps}
