#! /bin/sh
# deamon for klm-1.2
#
# klm [-DCMSAkRblrchw] [-N interface] [-m message] <device>
#
# Add your options :
# -D      run on the background (needed for daemon)
# -C      monitor the CPU level
# -N	  monitor the network traffic
# -M      monitor the memory level
# -S      monitor the swap level
# -A      chose randomly a design mode at startup
# -k      K2000 design mode
# -R      random design mode
# -b      bounce design mode
# -l      left design mode
# -r      right design mode
# -c      center design mode
# -m	  converts your message to morse code (e.g. klm -m \"Test monkey\" /dev/tty1)
# -h      prints out this message
# -w      prints out warranty
# <device> /dev/tty1, /dev/console, ...
# exemple : klm -D -k /dev/console

DAEMON_OPTS="-D -A /dev/console"


PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin
DAEMON=/usr/sbin/klm
NAME=klm
DESC=klm

test -x $DAEMON || exit 0

case "$1" in
  start)
	echo "Starting $DESC."
	exec $DAEMON $DAEMON_OPTS
	;;
  stop)
	echo "Stopping $DESC."
	exec killall $DAEMON
	;;
  restart)
	echo "Restarting $DESC"
	$0 stop
	sleep 1
	$0 start
	;;
  *)
	N=/etc/init.d/$NAME
	echo "Usage: $N {start|stop|restart}" >&2
	exit 1
	;;
esac

exit 0
