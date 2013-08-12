
typedef struct {
	double kp;	// Constant proportional multiplier
	double ki;	// Constant integral multiplier
	double kd;	// Constant derivitave multiplier
	double i;	// Integral
	double d;	// Derivitive
} pid;

// Initialize PID [Proportional Integral Derivitive] struct with constant multipliers
pid *init_pid(float kp, float ki, float kd);

double update_pid(pid *axis, double target, double value);

void set_kvals(pid *axis, double kp, double ki, double kd);

void delete_pid(pid *axis);
