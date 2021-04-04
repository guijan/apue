/* #define POSIX_C_SOURCE 200809L */
#define _XOPEN_SOURCE 700

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef int idtype_t;
#define P_PID 0
#define P_PGID 1
#define P_ALL 2

void err_sys(const char *const);
void pr_exit(int);
int waitid(idtype_t, id_t, siginfo_t, int);
void new_prexit(siginfo_t);

int
main(void)
{
	pid_t pid;
	int status;
	idtype_t idtype;
	id_t id;
	siginfo_t *infop;
	int options;

	if ((pid = fork()) == -1)
		err_sys("fork error");
	else if (pid == 0)
		exit(7);

	if (waitid(P_PID, pid, infop, WSTOPPED | WEXITED) == -1)
		err_sys("wait error");
	pr_exit(infop);

	if ((pid = fork()) == -1)
		err_sys("for error");
	else if (pid == 0)
		abort();

	if (waitid(P_PID, pid, infop, WSTOPPED | WEXITED) == -1)
		err_sys("wait error");

	pr_exit(infop);

	if ((pid = fork()) == -1)
		err_sys("fork error");
	else if (pid == 0)
		status /= 0;

	if (waitid(P_PID, pid, infop, WSTOPPED | WEXITED) == -1)
		err_sys("wait error");
	pr_exit(infop);

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

void
new_prexit(siginfo_t status)
{
	if (WIFEXITED(status.si_status))
		printf("normal termination, exit status =%d\n",
				WEXITSTATUS(status.si_status));
	else if (WIFSIGNALED(status.si_status))
		printf("abnormal termination, signal number = %d%s\n",
				WTERMSIG(status.si_status),
#ifdef WCOREDUMP
				WCOREDUMP(status.si_status) ?
				" (core file generated)" : "");
#else
							"");
#endif
	else if (WIFSTOPPED(status.si_status))
		printf("child stopped, signal number = %d\n",
				WSTOPSIG(status.si_status));
}
