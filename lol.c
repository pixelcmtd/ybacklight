#define MAX 3000

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	srand(time(0));
	char bfr[50];
	while(1)
	{
		sprintf(bfr, "ybacklight set %d", rand() % MAX);
		system(bfr);
	}
}
