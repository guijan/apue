#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	BUFFSIZE	4096

void err_sys(char *);

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");

	if (n < 0)
		err_sys("read error");

	exit(0);
}

void
err_sys(char *msg)
{
	fputs(msg, stderr);
	exit(1);
}
