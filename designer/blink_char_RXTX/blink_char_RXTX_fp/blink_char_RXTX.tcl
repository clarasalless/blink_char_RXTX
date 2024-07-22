open_project -project {C:\Users\Clara\Documents\blink_char_RXTX\designer\blink_char_RXTX\blink_char_RXTX_fp\blink_char_RXTX.pro}
enable_device -name {M2S005} -enable 1
set_programming_file -name {M2S005} -file {C:\Users\Clara\Documents\blink_char_RXTX\designer\blink_char_RXTX\blink_char_RXTX.ppd}
set_programming_action -action {PROGRAM} -name {M2S005} 
run_selected_actions
save_project
close_project
