typedef struct {
  double kp;
  double ki;
  double kd;
  double i;
  double d;
} pid;

pid *init_pid(float kp, float ki, float kd);
double update_pid(pid *axis,double target,double value);
void set_kvals(pid *axis,double kp,double ki,double kd);
void delete_pid(pid *axis);
