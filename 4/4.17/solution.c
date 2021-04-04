#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define FILE_MODE S_IRWXU | S_IRWXG | S_IRWXO

void die(const char *const);

int
main(void)
{
	int fd;
	char path[] = "/dev/fd/1";
	if ((fd = creat(path, FILE_MODE)) < 0)
		die(NULL);
}


void
die(const char *const msg)
{
	perror(NULL);
	exit(EXIT_FAILURE);
}
