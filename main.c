#define DEBUG 0
#include "config.h"
#include "ybacklight.c"
#define isnum(c) ((c) >= '0' && (c) <= '9')
#if DEBUG
#define debug(f, a) printf(f, a)
#else
#define debug(f, a)
#endif
#include <unistd.h>

int S = 0, w = 0, f = 0;
void run(char cmd, long *cur, long *max, long arg)
{
	debug("Cmd: %c; ", cmd);
	debug("Short: %d\n", *S);
	switch(cmd)
	{
		case 'c': printf("%ld", S ? *cur / SHORT_FACTOR : *cur); w = 1; break;
		case 'm': printf("%ld", S ? *max / SHORT_FACTOR : *max); w = 1; break;
		case 'S': S = 1; return;
		case 'i': *cur += S ? arg * SHORT_FACTOR : arg; f = 1; break;
		case 'd': *cur -= S ? arg * SHORT_FACTOR : arg; f = 1; break;
		case 's': *cur  = S ? arg * SHORT_FACTOR : arg; f = 1; break;
		default:  putchar(cmd); w = 1; break;
	}
	S = 0;
}

int main(int argc, char **argv)
{
#ifdef __OPENBSD__
        if(pledge("stdio unveil")) die("pledge: %s\n");
        if(unveil(BACKLIGHT, "rw")) die("unveil: %s\n");
        if(unveil(NULL, NULL)) die("unveil: %s\n");
#endif
	long cur = read_brightness(BRIGHTNESS);
	long max = read_brightness(MAX_BRIGHTNESS);
	char c, buf[NUM_MAX], q /*queued*/ = '\0';
	long a = -1;
	memset(buf, 0, NUM_MAX);
	for(int i = 1; i < argc; i++)
	{
		char *cp = argv[i];
		while((c = *cp++))
			if(isnum(c)) buf[strlen(buf)] = c;
			else
			{
				if(*buf) a = strtol(buf, 0, 10),
					 memset(buf, 0, NUM_MAX);
				if(q) run(q, &cur, &max, a),
                                      q = 0;
				if((c == 's' || c == 'd' || c == 'i')
				   && isnum(*(cp + 1))) q = c;
				else run(c, &cur, &max, a);
			}
	}
	if(strlen(buf) && q) run(q, &cur, &max, strtol(buf, 0, 10));
	if(w) putchar('\n');
	if(f) write_brightness(BRIGHTNESS, cur);
	return 0;
}
