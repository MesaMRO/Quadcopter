mkdir objs
rm objs/*.o
DEFINES="-DEMPL_TARGET_LINUX -DMPU9150 -DAK8975_SECONDARY"
INCLUDES="-I eMPL -I glue -I mpu9150"
for file in imu main network pid pwm
do
  gcc -c ${file}.c -Wall -g -o objs/${file}.o
done
for file in inv_mpu inv_mpu_dmp_motion_driver
do
  gcc -c eMPL/${file}.c $INCLUDES -o objs/${file}.o $DEFINES
done
for file in linux_glue
do
  gcc -c glue/${file}.c $INCLUDES -o objs/${file}.o $DEFINES
done
for file in mpu9150 quaternion vector3d
do
  gcc -c mpu9150/${file}.c $INCLUDES -o objs/${file}.o $DEFINES
done
gcc objs/*.o -g -lm -o cserver
