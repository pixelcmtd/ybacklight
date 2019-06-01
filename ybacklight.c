#include "config.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define USAGE() puts("c[ur]/S[hort]/m[ax]/i[nc]/d[ec]/s[et]")

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
#ifndef bool
typedef int bool;
#endif
struct display
{
	long cur;
	long max;
};
void run(char cmd, bool *S, struct display *d, long arg, bool *w)
{
	switch(cmd)
	{
		case 'c': printf("%ld", *S ? d->cur / 100 : d->cur); *w = 1; break;
		case 'm': printf("%ld", *S ? d->max / 100 : d->max); *w = 1; break;
		case 'S': *S = 1; return;
		case 'i': d->cur += arg; break;
		case 'd': d->cur -= arg; break;
		case 's': d->cur  = arg; break;
		default:  putchar(cmd); *w = 1; break;
	}
	*S = 0;
}
int main(int argc, char **argv)
{
	struct display d;
	d.cur = br_read(BRIGHTNESS);
	d.max = br_read(MAX_BRIGHTNESS);
	char c;
	char q = 0; //queued
	long a = -1;
	bool S = 0;
	char numbuf[NUM_MAX];
	memset(numbuf, 0, NUM_MAX);
	bool w = 0;
	for(int i = 1; i < argc; i++)
	{
		char *cp = argv[i];
		while((c = *cp++))
			if(c >= '0' && c <= '9')
				numbuf[strlen(numbuf)] = c;
			else
			{
				if(strlen(numbuf))
					a = strtol(numbuf, 0, 10),
					memset(numbuf, 0, NUM_MAX);
				if(q) run(q, &S, &d, a, &w), q = 0;
				if((c == 's' || c == 'd' || c == 'i') &&
				   *(cp+1) >= '0' && *(cp+1) <= '9')
					q = c;
				else run(c, &S, &d, a, &w);
			}
	}
	if(strlen(numbuf) && q)
		run(q, &S, &d, strtol(numbuf, 0, 10), &w);
	if(w) putchar('\n');
	write_brightness(d.cur);
	return 0;
}
#endif
