#include "include.h"

void load_config(char *bfr)
{
	FILE *f = fopen("/etc/ybacklight/dir.conf", "r");
	size_t i = fread(bfr, 1, 1024, f) - 1;
	fclose(f);
	if(bfr[i] == '\n')
		bfr[i] = '\0';
}

long read_brightness(char *dir)
{
	char c[2048];
	strcpy(c, dir);
	strcat(c, "brightness");
	char bfr[32];
	FILE *f = fopen(c, "r");
	size_t i = fread(bfr, 1, 32, f) - 1;
	fclose(f);
	if(bfr[i] == '\n')
		bfr[i] = '\0';
	return strtol(bfr, 0, 10);
}

long read_max_brightness(char *dir)
{
	char c[2048];
	strcpy(c, dir);
	strcat(c, "max_brightness");
	char bfr[32];
	FILE *f = fopen(c, "r");
	size_t i = fread(bfr, 1, 32, f) - 1;
	fclose(f);
	if(bfr[i] == '\n')
		bfr[i] = '\0';
	return strtol(bfr, 0, 10);
}

void write_brightness(char *dir, long i)
{
	char c[2048];
	strcpy(c, dir);
	strcat(c, "brightness");
	char bfr[32];
	sprintf(bfr, "%ld\n", i);
	FILE *f = fopen(c, "w");
	if(!f)
	{
		puts("No privileges.");
		return;
	}
	fwrite(bfr, 1, 32, f);
	fclose(f);
}
