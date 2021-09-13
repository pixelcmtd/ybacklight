CC ?= cc
CFLAGS ?= -O3 -s -Wall -Wextra -pedantic
PREFIX ?= /usr/local

all: ybacklight

ybacklight: ybacklight.c main.c config.h
	$(CC) main.c $(CFLAGS) -o ybacklight
	chmod 4755 ybacklight

install: all
	install -d $(PREFIX)/bin
	install -m 4755 ybacklight $(PREFIX)/bin/ybacklight

clean:
	rm -f ybacklight lol

test: all
	@./test.sh

lol: ybacklight.c lol.c config.h
	$(CC) lol.c $(CFLAGS) -o lol
	chmod 4755 lol

.PHONY: all clean test install
