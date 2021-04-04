#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void err_sys(const char *const);
void pr_exit(int);

int
main(void)
{
	pid_t pid;
	int status;
	if ((pid = fork()) == -1)
		err_sys("fork error");
	else if (pid == 0)
		exit(7);

	if (wait(&status) != pid)
		err_sys("wait error");
	pr_exit(status);

	if ((pid = fork()) == -1)
		err_sys("for error");
	else if (pid == 0)
		abort();

	if (wait(&status) != pid)
		err_sys("wait error");

	pr_exit(status);

	if ((pid = fork()) == -1)
		err_sys("fork error");
	else if (pid == 0)
		status /= 0;

	if (wait(&status) != pid)
		err_sys("wait error");
	pr_exit(status);

	exit(0);
}


void
err_sys(const char *const msg)
{
	perror(NULL);
	if (msg)
		fputs(msg, stderr);
	exit(EXIT_FAILURE);
}


void
pr_exit(int status)
{
	if (WIFEXITED(status))
		printf("normal termination, exit status = %d\n",
				WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	printf("abnormal termination, signal number = %d %s\n",
			WTERMSIG(status),
#ifdef WCOREDUMP
			WCOREDUMP(status) ? " (core file generated)" : "");
#else
									"");
#endif
	else if (WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n",
				WSTOPSIG(status));
}
