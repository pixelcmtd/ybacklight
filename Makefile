all:
	@sudo gcc ybacklight.c -O3 -s -o ybacklight
	@sudo chmod +s ybacklight

debug:
	@gcc ybacklight.c -Og -Wall -Wextra -pedantic -o ybacklight
	@chmod +s ybacklight
	@./ybacklight

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
	@./lol
