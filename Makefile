all:
	@sudo gcc main.c -O3 -s -o ybacklight
	@sudo chmod +s ybacklight

debug:
	@gcc main.c -Og -Wall -Wextra -pedantic -o ybacklight
	@chmod +s ybacklight

install: all
	@cp ybacklight /usr/bin/ybacklight
	@chmod +s /usr/bin/ybacklight

clean:
	@rm -f ybacklight lol

test: debug
	@./.test

lol:
	@sudo gcc lol.c -O3 -o lol
	@sudo chmod +s lol
	@sudo ./lol

.PHONY: all lol clean test debug install
