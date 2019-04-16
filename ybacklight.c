#include "config.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define USAGE() puts("cur, max, inc [long], dec [long] or set [long]")

void die(char *msg1, char *msg2)
{
	printf(msg1, msg2);
	exit(1);
}

long br_read(char *fname)
{
	char bfr[NUM_MAX];
	FILE *f = fopen(fname, "r");
	size_t i = fread(bfr, 1, NUM_MAX, f) - 1;
	fclose(f);
	if(bfr[i] == '\n') bfr[i] = '\0';
	return strtol(bfr, 0, 10);
}

void write_brightness(long i)
{
	char bfr[NUM_MAX];
	size_t cnt = sprintf(bfr, "%ld\n", i);
	uid_t uid = getuid();
	if(setuid(0)) die("Can't set UID: %s\n", strerror(errno));
	FILE *f = fopen(BRIGHTNESS, "w");
	if(!f) die("Can't open file: %s\n", strerror(errno));
	fwrite(bfr, 1, cnt, f);
	fclose(f);
	if(setuid(uid)) die("Can't set UID: %s\n", strerror(errno));
}

#ifndef YBACKLIGHT_LIB
int main(int argc, char **argv)
{
	long i = br_read(BRIGHTNESS);
	long j = br_read(MAX_BRIGHTNESS);
	if(argc < 2) printf("%ld/%ld\n", i, j);
	else if(argc == 2)
	{
		     if(*argv[1] == 'c') printf("%ld\n", i);
		else if(*argv[1] == 'm') printf("%ld\n", j);
		else 				 USAGE();
	}
	else if(*argv[1] == 'i')
		write_brightness(i + strtol(argv[2], 0, 0));
	else if(*argv[1] == 'd')
		write_brightness(i - strtol(argv[2], 0, 0));
	else if(*argv[1] == 's')
		write_brightness(strtol(argv[2], 0, 0));
	else USAGE();
}
#endif
