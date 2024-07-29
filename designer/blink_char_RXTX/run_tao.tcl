set_device -family {SmartFusion2} -die {M2S005} -speed {STD}
read_verilog -mode system_verilog {C:\Users\Clara\Documents\blink_char_RXTX\component\work\blink_char_RXTX_sb\CCC_0\blink_char_RXTX_sb_CCC_0_FCCC.v}
read_verilog -mode system_verilog {C:\Users\Clara\Documents\blink_char_RXTX\component\work\blink_char_RXTX_sb\FABOSC_0\blink_char_RXTX_sb_FABOSC_0_OSC.v}
read_verilog -mode system_verilog {C:\Users\Clara\Documents\blink_char_RXTX\component\work\blink_char_RXTX_sb_MSS\blink_char_RXTX_sb_MSS.v}
read_verilog -mode system_verilog {C:\Users\Clara\Documents\blink_char_RXTX\component\Actel\DirectCore\CoreResetP\7.1.100\rtl\vlog\core\coreresetp_pcie_hotreset.v}
read_verilog -mode system_verilog {C:\Users\Clara\Documents\blink_char_RXTX\component\Actel\DirectCore\CoreResetP\7.1.100\rtl\vlog\core\coreresetp.v}
read_verilog -mode system_verilog -lib COREAPB3_LIB {C:\Users\Clara\Documents\blink_char_RXTX\component\Actel\DirectCore\CoreAPB3\4.1.100\rtl\vlog\core\coreapb3_muxptob3.v}
read_verilog -mode system_verilog -lib COREAPB3_LIB {C:\Users\Clara\Documents\blink_char_RXTX\component\Actel\DirectCore\CoreAPB3\4.1.100\rtl\vlog\core\coreapb3_iaddr_reg.v}
read_verilog -mode system_verilog -lib COREAPB3_LIB {C:\Users\Clara\Documents\blink_char_RXTX\component\Actel\DirectCore\CoreAPB3\4.1.100\rtl\vlog\core\coreapb3.v}
read_verilog -mode system_verilog -lib CORETIMER_LIB {C:\Users\Clara\Documents\blink_char_RXTX\component\Actel\DirectCore\CoreTimer\2.0.103\rtl\vlog\core\coretimer.v}
read_verilog -mode system_verilog {C:\Users\Clara\Documents\blink_char_RXTX\component\work\blink_char_RXTX_sb\blink_char_RXTX_sb.v}
read_verilog -mode system_verilog {C:\Users\Clara\Documents\blink_char_RXTX\component\work\blink_char_RXTX\blink_char_RXTX.v}
set_top_level {blink_char_RXTX}
map_netlist
check_constraints {C:\Users\Clara\Documents\blink_char_RXTX\constraint\synthesis_sdc_errors.log}
write_fdc {C:\Users\Clara\Documents\blink_char_RXTX\designer\blink_char_RXTX\synthesis.fdc}
