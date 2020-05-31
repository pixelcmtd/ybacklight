#define DEBUG 0
#define NUM_MAX 16
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define die(msg) printf(msg, strerror(errno)), exit(1);

long read_brightness(char *fname)
{
	char bfr[NUM_MAX];
	FILE *f = fopen(fname, "r");
        if(!f) die("fopen: %s\n");
	bfr[fread(bfr, 1, NUM_MAX, f) - 1] = '\0';
	fclose(f);
	return strtol(bfr, 0, 10);
}

void write_brightness(char *fname, long i)
{
	char bfr[NUM_MAX];
	size_t cnt = sprintf(bfr, "%ld\n", i);
	uid_t uid = getuid();
	if(uid && setuid(0)) die("setuid(0): %s\n");
	FILE *f = fopen(fname, "w");
	if(!f) die("fopen: %s\n");
	fwrite(bfr, 1, cnt, f);
	fclose(f);
	if(uid && setuid(uid)) die("setuid(uid): %s\n");
}
