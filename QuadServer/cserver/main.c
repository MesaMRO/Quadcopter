#include "network.h"
#include "pid.h"
#include "pwm.h"
#include "imu.h"
#include <sys/select.h>

int main(int argc,char **argv) {
  int i; //iterator
  pid *x,*y,*z; //structs representing 3 pid controllers
  FILE *motors[4]; //array of PWM controllers for the motors
  imu_t *imu;
  fd_set net_set;
  double oldmag,magdiff;
  struct timeval timeout;
  int axes[4] = {0,0,0,0}; // 
  int x_adjust, y_adjust, z_adjust;
  int clientSock = init_net(); // Initialize network, get client socket
  x=init_pid(1,1,1);
  y=init_pid(1,1,1);
  z=init_pid(1,1,1);
  timeout.tv_sec=0;
  timeout.tv_usec=10000;
  for(i=0;i<4;i++) { //initialize PWM modules
    motors[i]=init_pwm(i);
  }
  imu = init_imu();
  update_imu(imu);
  oldmag=imu->mpu.fusedEuler[VEC3_Z] * RAD_TO_DEGREE;
  while(1) {
    printf("test\n");
    FD_ZERO(&net_set);
    FD_SET(clientSock, &net_set);
    if(select(clientSock + 1, &net_set, (fd_set *) 0, (fd_set *) 0, &timeout) == 1) {
      printf("clientSock\n");
      //read from clientSock
      update_axis(clientSock, &axes);
    } else {
      //update imu
      update_imu(imu);
      timeout.tv_sec=0;
      timeout.tv_usec=10000;
      magdiff=imu->mpu.fusedEuler[VEC3_Z] * RAD_TO_DEGREE-oldmag;
      if(magdiff>300) {
        magdiff-=360;
      }
      if(magdiff<-300) {
        magdiff+=360;
      }
      x_adjust = update_pid(x,axes[1]*.00061,imu->mpu.fusedEuler[VEC3_X] * RAD_TO_DEGREE);
      y_adjust = update_pid(y,axes[2]*.00061,imu->mpu.fusedEuler[VEC3_Y] * RAD_TO_DEGREE);
      z_adjust = update_pid(z,axes[3]*.00061,magdiff);
      oldmag=imu->mpu.fusedEuler[VEC3_Z] * RAD_TO_DEGREE;
      set_duty(motors[0], 1000000 + axes[0] * 14 + x_adjust - y_adjust + z_adjust);
      set_duty(motors[1],1000000+axes[0]*14-x_adjust-y_adjust-z_adjust);
      set_duty(motors[2],1000000+axes[0]*14+x_adjust+y_adjust-z_adjust);
      set_duty(motors[3],1000000+axes[0]*14-x_adjust+y_adjust+z_adjust);
    }
  }
}
