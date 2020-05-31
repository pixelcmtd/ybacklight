#define MAX 3000

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "config.h"
#include "ybacklight.c"

int main()
{
        if(getuid() && setuid(0)) die("setuid(0) in lol: %s\n");
	while(1) write_brightness(BRIGHTNESS, rand() % MAX), usleep(100000);
}
