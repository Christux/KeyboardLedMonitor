CC=gcc
CFLAGS=
DESTDIR=
BINDIR=/usr/sbin/

all: klm

docker:
	docker build -t keyboard-led-monitor .

docker-run: docker
	docker run -d --name klm --restart always --privileged -v /dev/tty7:/dev/tty1 --network none keyboard-led-monitor

klm: klm.c
	$(CC) $(CFLAGS) klm.c morse.c -o klm

clean:
	rm -f klm klm.o

install: klm
	install -d -m 0755 -o root -g root $(DESTDIR)/$(BINDIR)
	install -m 0755 -o root -g root klm $(DESTDIR)/$(BINDIR)

docker-clean:
	docker stop klm; \
	docker rm -f klm; \
	docker rmi -f keyboard-led-monitor;
