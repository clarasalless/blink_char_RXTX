set_component blink_char_RXTX_sb_MSS
# Microchip Technology Inc.
# Date: 2024-Jul-05 14:15:06
#

create_clock -period 40 [ get_pins { MSS_ADLIB_INST/CLK_CONFIG_APB } ]
set_false_path -ignore_errors -through [ get_pins { MSS_ADLIB_INST/CONFIG_PRESET_N } ]
