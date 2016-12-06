CC=gcc
CFLAGS=
DESTDIR=
BINDIR=/usr/sbin/

all: klm

klm: klm.c
	$(CC) $(CFLAGS) klm.c morse.c -o klm

clean: 
	rm -f klm klm.o

install: klm
	install -d -m 0755 -o root -g root $(DESTDIR)/$(BINDIR)
	install -m 0755 -o root -g root klm $(DESTDIR)/$(BINDIR)
