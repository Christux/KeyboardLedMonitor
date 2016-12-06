# Keyboard Led Monitor

Copyright (C) 2007 Christux
License GPL : http://www.gnu.org/copyleft/gpl.html

## Summary :

Keyboard Led Monitor is a free software which can monitor the utilization of resources with the leds of the keyboard (num lock, caps lock, scroll lock). The monitoring looks like the battery status bar of a mobile phone. Monitoring of CPU level, network traffic, memory  and swap usage, and battery level are supported. The software can be used with game modes also, like the program bl.

Battery monitoring is only activated if the AC adapter is plugged out, another monitor (or game mode) can be used when the battery is not in use. There is a security option which turns off the computer if the battery level < 4 %. Be very careful with this option, it runs a "/usr/sbin/halt" so the computer will chut down with no saving of your works !! A last point, ACPI support by kernel is required for battery monitoring.

## Development Status :

I write this software first to monitor the battery level because I wanted to see it without to go on the deskbar. After discussions with some friends, I add some others monitors and game modes inspired from the software bl.

## Thanks :

Thanks to Greg Hankins and Ed Doolittle for the blinkenlights program which inspired me.

## Installation :

If you have a program which uses leds of the keyboard (like bl), remove it before to continue.

Extract the files, type make and make install.
Install the daemon manually.


## Usage :

klm [-DBsCMSkRblrchw] [-N interface] <device>
-D 	run on the background (needed for daemon)
-B 	monitor the battery level (acpi is needed)
-s
	security (turn off the computer when the battery level < 4 %)
-C 	monitor the CPU level
-N
	monitor the network traffic
-M 	monitor the memory level
-S 	monitor the swap level
-k 	K2000 design mode
-R 	random design mode
-b 	bounce design mode
-l
	left design mode
-r 	right design mode
-c 	center design mode
-h 	prints out this message
-w 	prints out warranty
<device> /dev/tty1, /dev/tty2, ...

## Examples :

'''
klm -D -B -k /dev/tty1
'''
The program will work in background, if you are connected to a AC adapter, the K2000 mode will run, in the other case, the battery will be monitored.

'''
klm -D -B /dev/tty1
'''
The program will work in background, if you are not connected to a AC adapter the battery will be monitored.

'''
klm -C /dev/tty1
'''
Monitoring CPU.

'''
klm -N eth0 /dev/tty1
'''
Monitoring network traffic.

NB : You need root rights to access the leds. Better use :
'''
sudo klm [-DBsCMSkRblrchw] [-N interface] <device>
'''

## Daemon :

To configure the daemon (for Debian), edit the file /etc/init.d/klm.
You will see default options are "-D -C /dev/tty1", it is the monitoring of the CPU. You can modify the device or add a mode like this : "-D -B -s -k /dev/tty3". After modification, restart the daemon : "/etc/init.d/klm restart".

## Keyboard Leds order :

The default leds order is (left to right) : num lock - caps lock - scroll lock.  If your keyboard is different, it is my case, download the sources and edit klm.c . At the beginning the leds order is defined, you can modifie it here. 