#include "mpu9150/mpu9150.h"
typedef struct {
  mpudata_t mpu;
} imu_t;
imu_t *init_imu();
void update_imu(imu_t *imu);
