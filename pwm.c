#include "pwm.h"

/*
 * PWM setup
 * FOSC/4 with a prescaler of 4
 * PR2 of 255 for 245Hz
 * 10 bit PWM resolution
 * PWM3 on RA1
 * PWM4 on RA0
*/
void init_pwm(void) {
    T2CLKCON = 0x01;
    T2CON = 0x10;
    PR2 = 255;
    RA1PPS = 0x0B;
    PWM3CON = 0x80;
    RA0PPS = 0x0C;
    PWM4CON = 0x80;
}

void pwm_wrduty(volatile uint8_t *pwm, uint16_t duty) {
    *pwm = ((duty >> 2) & 0xFF); 
    *(pwm - 1) = ((duty << 6) & 0xC0);
}

uint16_t pwm_rdduty(volatile uint8_t *pwm) {
    uint16_t duty;
    duty = *pwm;
    duty = duty << 2;
    duty |= ((*pwm -1) >> 6);
    
    return duty;
}

void pwm_increase(volatile uint8_t *pwm) {
    uint16_t duty = pwm_rdduty(pwm);
    duty += 102;
    if (duty <= 918) {
        pwm_wrduty(pwm, duty);
    }
}

void pwm_decrease(volatile uint8_t *pwm) {
    uint16_t duty = pwm_rdduty(pwm);
    duty -= 102;
    if (duty >= 102) {
        pwm_wrduty(pwm, duty);
    }
}