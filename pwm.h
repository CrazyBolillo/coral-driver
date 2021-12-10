#ifndef __PWM_GUARD__
#define __PWM_GUARD__

#include <stdint.h>
#include <xc.h>

void init_pwm(void);

void pwm_wrduty(volatile uint8_t *pwm, uint16_t duty);
uint16_t pwm_rdduty(volatile uint8_t *pwm);

void pwm_increase(volatile uint8_t *pwm);
void pwm_decrease(volatile uint8_t *pwm);
#endif