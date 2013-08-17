#include <stdlib.h>
#include "imu.h"
#include "mpu9150/mpu9150.h"
imu_t *init_imu() {
  imu_t *imu = malloc(sizeof(imu_t));
  mpu9150_init(1, 100, 4);
  return imu;
}
void update_imu(imu_t *imu) {
  mpu9150_read(&(imu->mpu));
}
