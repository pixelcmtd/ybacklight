#include "io.c"

int main(int argc, char **argv)
{
	char dir[1024];
	load_config(dir);
	long i = read_brightness(dir);
	long j = read_max_brightness(dir);
	if(argc < 2)
		printf("%ld/%ld\n", i, j);
	else if(!strcmp(argv[1], "inc"))
		write_brightness(dir, i + strtol(argv[2], 0, 0));
	else if(!strcmp(argv[1], "dec"))
		write_brightness(dir, i - strtol(argv[2], 0, 0));
	else if(!strcmp(argv[1], "set"))
		write_brightness(dir, strtol(argv[2], 0, 0));
	return 0;
}
