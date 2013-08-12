#include <stdio.h>
#include <stdlib.h>
typedef struct {
  FILE *pwmfile;
} pwm;
  
pwm *init_pwm(int pin);
void set_duty(pwm *motor,int duty);
