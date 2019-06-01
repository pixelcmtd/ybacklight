#define MAX 3000

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define YBACKLIGHT_LIB
#include "ybacklight.c"

int main()
{
	srand(time(0));
	while(1) write_brightness(rand() % MAX), usleep(100000);
}
