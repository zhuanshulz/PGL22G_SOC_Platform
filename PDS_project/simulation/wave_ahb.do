onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /m1_test/uut/HCLK
add wave -noupdate /m1_test/uut/mem_cs
add wave -noupdate /m1_test/uut/raddr
add wave -noupdate /m1_test/uut/rdata1
add wave -noupdate /m1_test/uut/HCLK
add wave -noupdate /m1_test/uut/mem_cs[0]
add wave -noupdate /m1_test/uut/a_wr_en
add wave -noupdate /m1_test/uut/waddr
add wave -noupdate /m1_test/uut/wdata
add wave -noupdate /m1_test/uut/SD_nCS
add wave -noupdate /m1_test/uut/SD_DCLK
add wave -noupdate /m1_test/uut/SD_MOSI
add wave -noupdate /m1_test/uut/SD_MISO


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
