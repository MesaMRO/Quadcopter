cp ../../Device_Tree/MULTC-00A0.dtbo /lib/firmware/
echo MULTC > /sys/devices/bone_capemgr.8/slots
sleep 1
./throttle.sh 900000
