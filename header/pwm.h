#ifndef __pwm_h__
#define __pwm_h__

void PWM_off(unsigned char channel);
void PWM_on(unsigned char channel, float prescaler);
void set_PWM(unsigned char channel, float frequency);

#endif
