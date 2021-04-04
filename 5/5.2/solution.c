#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 4

void err_sys(const char*);

int
main(void)
{
	char buf[MAXLINE];
	while (fgets(buf, MAXLINE, stdin) != NULL)
		if (fputs(buf, stdout) == EOF)
			err_sys("output error");
	if (ferror(stdin))
		err_sys("input error");
	exit(0);
}

void
err_sys(const char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
