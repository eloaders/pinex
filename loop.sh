#!/bin/bash 
         for i in `seq 1 13`;
	 do
              cat /sys/bus/w1/devices/*/w1_slave
	      echo $i
         done
