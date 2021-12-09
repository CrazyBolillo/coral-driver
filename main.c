/*
 * File:   main.c
 * Author: anton
 *
 * Created on December 5, 2021, 11:23 PM
 */

// CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINT1  // Power-up default value for COSC bits (HFINTOSC (1MHz))
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; i/o or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (FSCM timer disabled)

// CONFIG2
#pragma config MCLRE = OFF      // Master Clear Enable bit (MCLR pin function is port defined function)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = OFF      // Brown-out reset enable bits (Brown-out reset disabled)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices)
#pragma config ZCD = OFF        // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR.)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit can be cleared and set only once in software)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)

// CONFIG3
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled, SWDTEN is ignored)
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4
#pragma config BBSIZE = BB512   // Boot Block Size Selection bits (512 words boot block size)
#pragma config BBEN = OFF       // Boot Block Enable bit (Boot Block disabled)
#pragma config SAFEN = OFF      // SAF Enable bit (SAF disabled)
#pragma config WRTAPP = OFF     // Application Block Write Protection bit (Application Block not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block not write protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration Register not write protected)
#pragma config WRTSAF = OFF     // Storage Area Flash Write Protection bit (SAF not write protected)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.)

// CONFIG5
#pragma config CP = OFF         // UserNVM Program memory code protection bit (UserNVM code protection disabled)

#include <xc.h>

#define _XTAL_FREQ 1000000

void main(void) {
    /*
     * Pins RA5:2 used as input pins with internal pull-ups enabled
     * Pins RA1:0 used to drive PWM. Set as output
     */
    LATA = 0x00;
    ANSELA = 0x00;
    TRISA = 0xFC;
    WPUA = 0b00111100;
    RA5PPS = 0x05;
    RA4PPS = 0x04;
    RA3PPS = 0x03;
    RA2PPS = 0x02;
    
    /*
     * PWM setup
     * FOSC/4 with a prescaler of 4
     * PR2 of 255 for 245Hz
     * 10 bit PWM resolution
     * PWM3 on RA1
     * PWM4 on RA0
     */
    T2CLKCON = 0x01;
    T2CON = 0x10;
    PR2 = 255;
    RA1PPS = 0x0B;
    PWM3CON = 0x80;
    RA0PPS = 0x0C;
    PWM4CON = 0x80;
    
    // For test purposes. 50% duty cycle
    // TODO: Read duty cycle from memory
    PWM3DCH = 0x80;
    PWM3DCL = 0x00;
    PWM4DCH = 0x80;
    PWM4DCL = 0x00;
    
    T2CONbits.TMR2ON = 1;
    while (1) {
        // TODO: Increase/decrease PWM duty cycle based on user input (clicks)
    }
}
