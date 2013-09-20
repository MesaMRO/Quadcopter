#include "network.h"
#include "pid.h"
#include "pwm.h"
#include "imu.h"
#include <sys/select.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <strings.h>

FILE *motors[4]; //array of PWM controllers for the motors

void exit_fxn(int asdf) {
  //printf("quitting\n");
  int i=0;
  for(i=0;i<4;i++) {
    set_duty(motors[i],900000);
  }
  close(server_socket);
  exit(1);
}

void register_int() {
	struct sigaction sia;

	bzero(&sia, sizeof sia);
	sia.sa_handler = exit_fxn;
	if (sigaction(SIGINT, &sia, NULL) < 0) {
		perror("sigaction(SIGINT)");
		exit(1);
	}
}
#define REFRESH_TIME 10000
int main(int argc,char **argv) {
  int i; //iterator
  pid *x,*y,*z; //structs representing 3 pid controllers
  imu_t *imu;
  fd_set net_set;
  double oldmag,magdiff;
  struct timeval timeout;
<<<<<<< HEAD
  int axes[4] = {0,0,0,0}; // 
  int x_adjust, y_adjust, z_adjust;
  int clientSock = init_net(); // Initialize network, get client socket
  x=init_pid(1,1,1);
  y=init_pid(1,1,1);
  z=init_pid(1,1,1);
=======
  int axes[4]={0,0,0,0};
  int x_adjust,y_adjust,z_adjust;
  int sock = init_net();
  register_int();
  x=init_pid(3500,000,000);
  y=init_pid(3400,000,1000);
  z=init_pid(000,000,000);
>>>>>>> 589bae4a7216ce11db80cd562162bc5624b07ecb
  timeout.tv_sec=0;
  timeout.tv_usec=REFRESH_TIME;
  for(i=0;i<4;i++) { //initialize PWM modules
    motors[i]=init_pwm(i);
  }
  imu = init_imu();
  update_imu(imu);
  oldmag=imu->mpu.fusedEuler[VEC3_Z] * RAD_TO_DEGREE;
  while(1) {
    ////printf("loop\n");
    FD_ZERO(&net_set);
<<<<<<< HEAD
    FD_SET(clientSock, &net_set);
    if(select(clientSock + 1, &net_set, (fd_set *) 0, (fd_set *) 0, &timeout) == 1) {
      printf("clientSock\n");
      //read from clientSock
      update_axis(clientSock, &axes);
=======
    FD_SET(sock,&net_set);
    if(select(sock+1,&net_set,(fd_set *) 0,(fd_set *) 0, &timeout)==1) {
      ////printf("reading from the socket\n");
      //read from sock
      if(!update_axis(sock,axes)) {
        break;
      }
>>>>>>> 589bae4a7216ce11db80cd562162bc5624b07ecb
    } else {
      ////printf("reading from the imu\n");
      //update imu
      update_imu(imu);
      timeout.tv_sec=0;
      timeout.tv_usec=REFRESH_TIME;
      magdiff=imu->mpu.fusedEuler[VEC3_Z] * RAD_TO_DEGREE-oldmag;
      if(magdiff>300) {
        magdiff-=360;
      }
      if(magdiff<-300) {
        magdiff+=360;
      }
      x_adjust = update_pid(x,0/*axes[1]*.00061*/,imu->mpu.fusedEuler[VEC3_X] * RAD_TO_DEGREE);
      y_adjust = update_pid(y,0/*axes[2]*.00061*/,imu->mpu.fusedEuler[VEC3_Y] * RAD_TO_DEGREE);
      //printf("X axis value: %lf\n",imu->mpu.fusedEuler[VEC3_X]*RAD_TO_DEGREE);
      //printf("Y axis value: %lf\n",imu->mpu.fusedEuler[VEC3_Y]*RAD_TO_DEGREE);
      z_adjust = update_pid(z,axes[3]*.00061,magdiff);
      oldmag=imu->mpu.fusedEuler[VEC3_Z] * RAD_TO_DEGREE;
<<<<<<< HEAD
      set_duty(motors[0], 1000000 + axes[0] * 14 + x_adjust - y_adjust + z_adjust);
      set_duty(motors[1],1000000+axes[0]*14-x_adjust-y_adjust-z_adjust);
      set_duty(motors[2],1000000+axes[0]*14+x_adjust+y_adjust-z_adjust);
      set_duty(motors[3],1000000+axes[0]*14-x_adjust+y_adjust+z_adjust);
=======
      set_duty(motors[0],900000+axes[0]*16-z_adjust-y_adjust+x_adjust);
      set_duty(motors[1],900000+axes[0]*16+z_adjust-y_adjust-x_adjust);
      set_duty(motors[2],900000+axes[0]*16-z_adjust+y_adjust-x_adjust);
      set_duty(motors[3],900000+axes[0]*16+z_adjust+y_adjust+x_adjust);
>>>>>>> 589bae4a7216ce11db80cd562162bc5624b07ecb
    }
  }
  exit_fxn(0);
}
