#define CONFIG "/etc/ybacklight/dir.conf"
#define MAX_CFG_LEN 1024
#define NUM_MAX 16
#define ROOT 0

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void load_config(char *bfr)
{
	FILE *f = fopen(CONFIG, "r");
	size_t i = fread(bfr, 1, MAX_CFG_LEN, f) - 1;
	fclose(f);
	if(bfr[i] == '\n')
		bfr[i] = '\0';
}

long read_brightness(char *dir)
{
	char c[MAX_CFG_LEN + 16];
	strcpy(c, dir);
	strcat(c, "brightness");
	char bfr[NUM_MAX];
	FILE *f = fopen(c, "r");
	size_t i = fread(bfr, 1, NUM_MAX, f) - 1;
	fclose(f);
	if(bfr[i] == '\n')
		bfr[i] = '\0';
	return strtol(bfr, 0, 10);
}

long read_max_brightness(char *dir)
{
	char c[MAX_CFG_LEN + 16];
	strcpy(c, dir);
	strcat(c, "max_brightness");
	char bfr[NUM_MAX];
	FILE *f = fopen(c, "r");
	size_t i = fread(bfr, 1, NUM_MAX, f) - 1;
	fclose(f);
	if(bfr[i] == '\n')
		bfr[i] = '\0';
	return strtol(bfr, 0, 10);
}

void write_brightness(char *dir, long i)
{
	char c[2048];
	strcpy(c, dir);
	strcpy(c+strlen(dir), "brightness");
	char bfr[NUM_MAX];
	sprintf(bfr, "%ld\n", i);
	uid_t uid = getuid();
	int j = setuid(ROOT);
	int en = errno;
	FILE *f = fopen(c, "w");
	if(!f)
	{
		printf("No privileges, because");
		if(j)
			printf(" setting the UID failed: %s\n",
					strerror(en));
		else
			printf("...I don't know, maybe this one: %s\n",
					strerror(errno));
		return;
	}
	fwrite(bfr, 1, strlen(bfr), f);
	fclose(f);
	setuid(uid);
}
