open_project -project {C:\Users\Clara\Documents\blink_char_RXTX\designer\blink_char_RXTX\blink_char_RXTX_fp\blink_char_RXTX.pro}\
         -connect_programmers {FALSE}
load_programming_data \
    -name {M2S005} \
    -fpga {C:\Users\Clara\Documents\blink_char_RXTX\designer\blink_char_RXTX\blink_char_RXTX.map} \
    -header {C:\Users\Clara\Documents\blink_char_RXTX\designer\blink_char_RXTX\blink_char_RXTX.hdr} \
    -spm {C:\Users\Clara\Documents\blink_char_RXTX\designer\blink_char_RXTX\blink_char_RXTX.spm} \
    -dca {C:\Users\Clara\Documents\blink_char_RXTX\designer\blink_char_RXTX\blink_char_RXTX.dca}
export_single_ppd \
    -name {M2S005} \
    -file {C:\Users\Clara\Documents\blink_char_RXTX\designer\blink_char_RXTX\blink_char_RXTX.ppd}

save_project
close_project
