#include "pwm.h"
#include <stdio.h>

int pwm_pins[][3] = {
	{8, 13, 18},//rr
	{8, 19, 19},//rl
	{9, 21, 16},//fr
	{9, 22, 17}//fl
};

const char path[] = "/sys/devices/ocp.2/P%d_%d.%d/duty";

FILE *init_pwm(int pin) {
  FILE *test;
  /*pwm *motor = malloc(sizeof(pwm));
  if(!motor) {
    return 0;
  }*/
  char filename[sizeof(path)+1];
  sprintf(filename,path,pwm_pins[pin][0],pwm_pins[pin][1],pwm_pins[pin][2]);
  test = fopen(filename,"w");
  if(!test) {
    printf("failed to open file: %s\n",filename);
    return 0;
  }
  //printf("%p\n",motor->pwmfile);
  //motor->pwmfile = test;
  set_duty(test,1000000);
  printf("motor %d init\n",pin);
  return test;
}

void set_duty(FILE *motor,int duty) {
  fprintf(motor,"%d",duty);
  //printf("power %d\n",duty);
  fflush(motor);
  fseek(motor,0,SEEK_SET);
}
