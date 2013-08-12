#include <stdlib.h>
#include "pid.h"

// Initialize PID [Proportional Integral Derivitive] struct with constant multipliers
pid *init_pid(float kp, float ki, float kd) {
	pid *new_axis = malloc(sizeof(pid));
	new_axis->kp = kp;
	new_axis->ki = ki;
	new_axis->kd = kd;
	new_axis->i = 0;
	new_axis->d = 0;
	return new_axis;
}

double update_pid(pid *axis,double target,double value) {
  double err;
  double output;
  double p_val;
  double i_val;
  double d_val;
  err = target - value;
  p_val = err * axis->kp;
  d_val=axis->kd*(err-axis->d);
  axis->d=err;
  axis->i+=err;
  i_val=axis->i*axis->ki;
  return p_val+i_val+d_val;
}

void set_kvals(pid *axis,double kp,double ki,double kd) {
  axis->kp=kp;
  axis->ki=ki;
  axis->kd=kd;
}

#define delete_pid free

