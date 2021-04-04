#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>

#define RWXRWXRWX S_IRWXU | S_IRWXG | S_IRWXO

int
main(void)
{
	char dir[] = "a";
	unsigned long dircount = 0;
	for (;; dircount++) {
		if (mkdir(dir, RWXRWXRWX) == -1)
			break;
		if (chdir(dir) == -1)
			break;
		printf("%lu\n", dircount);
	}

	printf("%s\n", getcwd(NULL, PATH_MAX * 4));
}
