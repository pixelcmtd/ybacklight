#include "config.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define parsenum(bfr) strtol((bfr), 0, 10)
#define isnum(c) (c) >= '0' && (c) <= '9'

void die(char *msg1, char *msg2)
{
	printf(msg1, msg2);
	exit(1);
}

long br_read(char *fname)
{
	char bfr[NUM_MAX];
	FILE *f = fopen(fname, "r");
	bfr[fread(bfr, 1, NUM_MAX, f) - 1] = '\0';
	fclose(f);
	return parsenum(bfr);
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
		case 'i': d->cur += *S ? arg * 100 : arg; break;
		case 'd': d->cur -= *S ? arg * 100 : arg; break;
		case 's': d->cur  = *S ? arg * 100 : arg; break;
		default:  putchar(cmd); *w = 1; break;
	}
	*S = 0;
}
int main(int argc, char **argv)
{
	struct display d;
	d.cur = br_read(BRIGHTNESS);
	d.max = br_read(MAX_BRIGHTNESS);
	char c, numbuf[NUM_MAX], q /*queued*/ = 0;
	long a = -1;
	bool S = 0, w = 0;
	memset(numbuf, 0, NUM_MAX);
	for(int i = 1; i < argc; i++)
	{
		char *cp = argv[i];
		while((c = *cp++))
			if(isnum(c)) numbuf[strlen(numbuf)] = c;
			else
			{
				if(strlen(numbuf))
					a = parsenum(numbuf),
					memset(numbuf, 0, NUM_MAX);
				if(q) run(q, &S, &d, a, &w), q = 0;
				if((c == 's' || c == 'd' || c == 'i')
				   && isnum(*(cp + 1))) q = c;
				else run(c, &S, &d, a, &w);
			}
	}
	if(strlen(numbuf) && q) run(q, &S, &d, parsenum(numbuf), &w);
	if(w) putchar('\n');
	write_brightness(d.cur);
	return 0;
}
#endif
