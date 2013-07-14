#include "etcp.h"

int main(int argc, char const *argv[])
{
	int cnt = 0;
	char line[1024];
	//setvbuf(stdout, NULL, _IOLBF, 0);
	while(fgets(line, sizeof(line), stdin) != NULL)
		printf("%3i:%s\n", ++cnt, line);
	return 0;
}