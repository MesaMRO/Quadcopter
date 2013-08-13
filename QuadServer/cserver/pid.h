// Pull data from IMU (PIM data)
// PID loop speed must account for IMU speed and client network speed

// PID [Proportional Integral Derivative] struct for individual axis
typedef struct {
	double kp;	// Proportional constant
	double ki;	// Integral constant
	double kd;	// Derivatave constant
	double i;	// Integral
	double d;	// Derivative
} pid;

// Initialize PID  struct with constant multipliers
pid *init_pid(float kp, float ki, float kd);

double update_pid(pid *axis, double target, double value);

void set_kvals(pid *axis, double kp, double ki, double kd);

void delete_pid(pid *axis);
