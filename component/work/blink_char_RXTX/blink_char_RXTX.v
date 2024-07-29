//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Wed Jul 24 14:50:03 2024
// Version: 2024.1 2024.1.0.3
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// blink_char_RXTX
module blink_char_RXTX(
    // Inputs
    DEVRST_N,
    MMUART_0_RXD_F2M,
    // Outputs
    GPIO_0_M2F,
    GPIO_1_M2F,
    MMUART_0_TXD_M2F
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  DEVRST_N;
input  MMUART_0_RXD_F2M;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output GPIO_0_M2F;
output GPIO_1_M2F;
output MMUART_0_TXD_M2F;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire   DEVRST_N;
wire   GPIO_0_M2F_net_0;
wire   GPIO_1_M2F_net_0;
wire   MMUART_0_RXD_F2M;
wire   MMUART_0_TXD_M2F_net_0;
wire   MMUART_0_TXD_M2F_net_1;
wire   GPIO_0_M2F_net_1;
wire   GPIO_1_M2F_net_1;
//--------------------------------------------------------------------
// TiedOff Nets
//--------------------------------------------------------------------
wire   VCC_net;
//--------------------------------------------------------------------
// Constant assignments
//--------------------------------------------------------------------
assign VCC_net = 1'b1;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign MMUART_0_TXD_M2F_net_1 = MMUART_0_TXD_M2F_net_0;
assign MMUART_0_TXD_M2F       = MMUART_0_TXD_M2F_net_1;
assign GPIO_0_M2F_net_1       = GPIO_0_M2F_net_0;
assign GPIO_0_M2F             = GPIO_0_M2F_net_1;
assign GPIO_1_M2F_net_1       = GPIO_1_M2F_net_0;
assign GPIO_1_M2F             = GPIO_1_M2F_net_1;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------blink_char_RXTX_sb
blink_char_RXTX_sb blink_char_RXTX_sb_0(
        // Inputs
        .FAB_RESET_N      ( VCC_net ),
        .DEVRST_N         ( DEVRST_N ),
        .MMUART_0_RXD_F2M ( MMUART_0_RXD_F2M ),
        // Outputs
        .POWER_ON_RESET_N (  ),
        .INIT_DONE        (  ),
        .FAB_CCC_GL0      (  ),
        .FAB_CCC_LOCK     (  ),
        .MSS_READY        (  ),
        .MMUART_0_TXD_M2F ( MMUART_0_TXD_M2F_net_0 ),
        .GPIO_0_M2F       ( GPIO_0_M2F_net_0 ),
        .GPIO_1_M2F       ( GPIO_1_M2F_net_0 ) 
        );


endmodule
