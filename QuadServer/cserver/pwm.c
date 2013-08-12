#include "pwm.h"

int pwm_pins[][]={{9,14,14},{9,16,15},{9,21,16},{9,22,17}};
const char *path = "/sys/device/ocp.2/P%d_%d.%d/duty";
pwm *init_pwm(int pin) {
  pwm *motor = malloc(sizeof(pwm));
  char filename[sizeof(path)+1];
  sprintf(filename,path,pwm_pins[pin][0],pwm_pins[pin][1],pwm_pins[pin][2]);
  motor->pwmfile = fopen(filename,"w");
  return motor;
}

void set_duty(pwm *motor,int duty) {
  fprintf(motor->pwmfile,"%d",duty);
  fflush(motor->pwmfile);
  fseek(motor->pwmfile,0,SEEK_SET);
}
