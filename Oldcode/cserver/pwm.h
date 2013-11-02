#include <stdio.h>
#include <stdlib.h>

/*typedef struct {
  FILE *pwmfile;
} pwm;*/
  
FILE *init_pwm(int pin);
void set_duty(FILE *motor,int duty);
