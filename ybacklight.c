#define DEBUG 0
#define NUM_MAX 16
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define die(msg) printf(msg ": %s\n", strerror(errno)), exit(1);

long long read_brightness(char *fname)
{
        char bfr[NUM_MAX];
        FILE *f = fopen(fname, "r");
        if(!f) die("fopen");
        bfr[fread(bfr, 1, NUM_MAX, f) - 1] = '\0';
        fclose(f);
        return strtoll(bfr, 0, 10);
}

void write_brightness(char *fname, long long i)
{
	char bfr[NUM_MAX];
	size_t cnt = sprintf(bfr, "%lld\n", i);
	uid_t uid = getuid();
	if(uid && setuid(0)) die("setuid(0)");
	FILE *f = fopen(fname, "w");
	if(!f) die("fopen");
	fwrite(bfr, 1, cnt, f);
	fclose(f);
	if(uid && setuid(uid)) die("setuid(uid)");
}
