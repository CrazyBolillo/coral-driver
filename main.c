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
#include "pwm.h"
#include "keys.h"

#define _XTAL_FREQ 1000000

#define STATUS_BLINK_SEP 'S'
#define STATUS_BLINK_TOG 'T'
#define STATUS_FIXED 'F'

uint8_t click;
uint8_t status = STATUS_FIXED;

void main(void) {
    /*
     * Pins RA5:2 used as input pins with internal pull-ups enabled
     * Pins RA1:0 used to drive PWM. Set as output
     */
    LATA = 0x00;
    ANSELA = 0x00;
    TRISA = 0xFC;
    WPUA = TRISA;
    RA5PPS = 0x05;
    RA4PPS = 0x04;
    RA3PPS = 0x03;
    RA2PPS = 0x02;
    
    init_pwm();
    pwm_wrduty(&PWM3DCH, 256);
    pwm_wrduty(&PWM4DCH, 256);
    pwm_on();
    
    while (1) {
        click = read_click();
        if (status == STATUS_FIXED) {
            switch (click) {
                case UP_CLICK:
                   pwm_increase(&PWM3DCH);
                   pwm_increase(&PWM4DCH);
                   break;
                case DOWN_CLICK:
                   pwm_decrease(&PWM3DCH);
                   pwm_decrease(&PWM4DCH);
                   break;
                case MODE_ONE_CLICK: 
                   status = STATUS_BLINK_TOG;
            } 
        }
        if (status == STATUS_BLINK_TOG) {
            // TODO IMPLEMENT TMR0 for blinking
        }  
    }
    
}
