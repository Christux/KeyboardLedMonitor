# Keyboard Led Monitor

Copyright (C) 2007 Christux
License GPL : http://www.gnu.org/copyleft/gpl.html

## Summary :

Keyboard Led Monitor is a free software able to monitor the use of computer resources thanks to the leds of the keyboard (num lock, caps lock, scroll lock). The monitoring looks like the battery status bar of a mobile phone. Monitoring of CPU level, network traffic, memory  and swap usage are supported. The software can be used with game modes also (knight rider, bounce, etc.).

## Development Status :

Stopped, but open to new ideas ;)

## Thanks :

Thanks to Greg Hankins and Ed Doolittle for the blinkenlights program that inspired me.</br>
Thanks to Nick Aschenbach for the morse mode and some code refactoring.

## Installation :

If you have a program which uses leds of the keyboard (like bl), remove it before to continue.

Extract the files, type make and make install.
Install the daemon manually.


## Usage :

klm [-DCMSkRblrchw] [-N interface] <device>
-D 	run on the background (needed for daemon)
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

```
klm -D -k /dev/tty1
```
The program works in background, the knight rider is running.

```
klm -C /dev/tty1
```
Monitoring CPU.

```
klm -N eth0 /dev/tty1
```
Monitoring network traffic.

NB : You need root rights to access the leds. Better use :
```
sudo klm [-DsCMSkRblrchw] [-N interface] <device>
```

## Daemon :

To configure the daemon (for Debian), edit the file /etc/init.d/klm.
You will see default options are "-D -C /dev/tty1", it is the monitoring of the CPU. You can modify the device or add a mode like this : "-D -k /dev/tty3". After modification, restart the daemon : "/etc/init.d/klm restart".

## Keyboard Leds order :

The default leds order is (left to right) : num lock - caps lock - scroll lock.  If your keyboard is different, you can edit "klm.h". The leds order is defined at the beginning of the file. 