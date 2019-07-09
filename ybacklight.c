#include "config.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define parsenum(bfr) (strtol((bfr), 0, 10))
#define isnum(c) ((c) >= '0' && (c) <= '9')
#define die(msg1, msg2) printf(msg1, msg2), exit(1);
#if DEBUG
#define debug(f, a) printf(f, a)
#else
#define debug(f, a)
#endif
#ifndef bool
typedef int bool;
#endif

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
bool S = 0, w = 0;
void run(char cmd, long *cur, long *max, long arg)
{
	debug("Cmd: %c; ", cmd);
	debug("Short: %d\n", *S);
	switch(cmd)
	{
		case 'c': printf("%ld", S ? *cur / SHORT_FACTOR : *cur); w = 1; break;
		case 'm': printf("%ld", S ? *max / SHORT_FACTOR : *max); w = 1; break;
		case 'S': S = 1; return;
		case 'i': *cur += S ? arg * SHORT_FACTOR : arg; break;
		case 'd': *cur -= S ? arg * SHORT_FACTOR : arg; break;
		case 's': *cur  = S ? arg * SHORT_FACTOR : arg; break;
		default:  putchar(cmd); w = 1; break;
	}
	S = 0;
}
int main(int argc, char **argv)
{
	long cur = br_read(BRIGHTNESS);
	long max = br_read(MAX_BRIGHTNESS);
	char c, buf[NUM_MAX], q /*queued*/ = 0;
	long a = -1;
	memset(buf, 0, NUM_MAX);
	for(int i = 1; i < argc; i++)
	{
		char *cp = argv[i];
		while((c = *cp++))
			if(isnum(c)) buf[strlen(buf)] = c;
			else
			{
				if(*buf) a = parsenum(buf),
					 memset(buf, 0, NUM_MAX);
				if(q) run(q, &cur, &max, a),
                                      q = 0;
				if((c == 's' || c == 'd' || c == 'i')
				   && isnum(*(cp + 1))) q = c;
				else run(c, &cur, &max, a);
			}
	}
	if(strlen(buf) && q) run(q, &cur, &max, parsenum(buf));
	if(w) putchar('\n');
	write_brightness(cur);
	return 0;
}
#endif
