#ifndef __KEYS_GUARD__
#define __KEYS_GUARD__

#include <stdint.h>
#include <xc.h>

#define _XTAL_FREQ 1000000

#define MODE_BTN PORTAbits.RA5
#define UP_BTN PORTAbits.RA4
#define POWER_BTN PORTAbits.RA3
#define DOWN_BTN PORTAbits.RA2

#define is_pushed(x, val) __delay_ms(32); if (x != 0) { return 0; } while (x == 0); return val;

#define MODE_ONE_CLICK 'A'
#define MODE_TWO_CLICK 'B'
#define UP_CLICK 'U'
#define DOWN_CLICK 'D'
#define POWER_CLICK 'P'

uint8_t read_click(void);

#endif