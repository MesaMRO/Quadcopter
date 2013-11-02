#!/bin/bash
echo $1
echo $1 > /sys/devices/ocp.2/P8_13.18/duty
echo $1 > /sys/devices/ocp.2/P8_19.19/duty
echo $1 > /sys/devices/ocp.2/P9_21.16/duty
echo $1 > /sys/devices/ocp.2/P9_22.17/duty
echo $1 > /sys/devices/ocp.2/P9_14.14/duty
echo $1 > /sys/devices/ocp.2/P9_16.15/duty
