new_project \
         -name {blink_char_RXTX} \
         -location {C:\Users\Clara\Documents\blink_char_RXTX\designer\blink_char_RXTX\blink_char_RXTX_fp} \
         -mode {chain} \
         -connect_programmers {FALSE}
add_actel_device \
         -device {M2S005} \
         -name {M2S005}
enable_device \
         -name {M2S005} \
         -enable {TRUE}
save_project
close_project
