debug:
	@gcc ybacklight.c -Og -fsanitize=address -Wall -Wextra -o ybacklight
	@./ybacklight
all:
	@sudo gcc ybacklight.c -O3 -o ybacklight
	@sudo chmod +s ybacklight
install: all
	@sudo cp ybacklight /usr/bin/ybacklight
	@sudo chmod +s /usr/bin/ybacklight
test:
	@./.test
