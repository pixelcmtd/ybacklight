#define CONFIG "/etc/ybacklight/dir.conf"
#define MAX_CFG_LEN 1024
#define NUM_MAX 16

#include <sys/types.h>
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

long br_read(char *dir, char *fname)
{
	char c[MAX_CFG_LEN + 16];
	strcpy(c, dir);
	strcat(c, fname);
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
	int j = setuid(0); //root
	int en = errno;
	FILE *f = fopen(c, "w");
	if(!f)
	{
		printf("No privileges");
		if(j)
			printf(", setting the UID failed: %s\n",
					strerror(en));
		else
			printf("...I don't know, can't open, errno: %s\n",
					strerror(errno));
		return;
	}
	fwrite(bfr, 1, strlen(bfr), f);
	fclose(f);
	setuid(uid);
}

int main(int argc, char **argv)
{
	char dir[MAX_CFG_LEN];
	load_config(dir);
	long i = br_read(dir, "brightness");
	long j = br_read(dir, "max_brightness");
	if(argc < 2)
		printf("%ld/%ld\n", i, j);
	else if(argc == 2)
	{
		if(!strcmp(argv[1], "cur"))
			printf("%ld\n", i);
		else if(!strcmp(argv[1], "max"))
			printf("%ld\n", j);
		else
			puts("cur, max, inc [long], dec [long] or set [long]");
	}
	else if(!strcmp(argv[1], "inc"))
		write_brightness(dir, i + strtol(argv[2], 0, 0));
	else if(!strcmp(argv[1], "dec"))
		write_brightness(dir, i - strtol(argv[2], 0, 0));
	else if(!strcmp(argv[1], "set"))
		write_brightness(dir, strtol(argv[2], 0, 0));
	return 0;
}
