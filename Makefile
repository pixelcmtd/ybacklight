all:
	@sudo gcc ybacklight.c -O3 -s -o ybacklight
	@sudo chmod +s ybacklight

debug:
	@gcc ybacklight.c -Og -Wall -Wextra -pedantic -o ybacklight
	@./ybacklight

install: all
	@sudo cp ybacklight /usr/bin/ybacklight
	@sudo chmod +s /usr/bin/ybacklight

test:
	@./.test

lol:
	@sudo gcc lol.c -o lol
	@sudo chmod +s lol
	@./lol
