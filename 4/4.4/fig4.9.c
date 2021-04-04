#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

void err_sys(const char *const);

int
main(void)
{
	umask(0);
	if (creat("foo", RWRWRW) < 0)
		err_sys("creat error for foo");
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("bar", RWRWRW) < 0)
		err_sys("creat error for bar");
	exit(0);
}

void
err_sys(const char *const msg)
{
	fprintf(stderr, "%s\n", msg);
	perror(NULL);
	exit(EXIT_FAILURE);
}
