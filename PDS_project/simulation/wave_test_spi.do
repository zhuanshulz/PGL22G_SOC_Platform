onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /m1_test/uut/TH_1S
add wave -noupdate /m1_test/uut/ex_clk_50m
add wave -noupdate /m1_test/uut/rst_key
add wave -noupdate /m1_test/uut/gpio_in0
add wave -noupdate /m1_test/uut/gpio_in1
add wave -noupdate /m1_test/uut/LED
add wave -noupdate /m1_test/uut/RX
add wave -noupdate /m1_test/uut/TX
add wave -noupdate /m1_test/uut/spi0_clk
add wave -noupdate /m1_test/uut/spi0_cs
add wave -noupdate /m1_test/uut/spi0_mosi
add wave -noupdate /m1_test/uut/spi0_miso
add wave -noupdate /m1_test/uut/spi1_clk
add wave -noupdate /m1_test/uut/spi1_cs
add wave -noupdate /m1_test/uut/spi1_mosi
add wave -noupdate /m1_test/uut/spi1_miso


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
