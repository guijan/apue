#include <errno.h>
#include <signal.h>
#include <stdio.h>

void err_ret(char *);

void
pr_mask(const char *str)
{
	sigset_t sigset;
	int errno_save;
	int i;
	char *signame;

	errno_save = errno;
	if (sigprocmask(0, NULL, &sigset) < 0) {
		err_ret("sigprocmask error");
	} else {
		for(i = 0; i <= NSIG; i++) {
			if (sigismember(&sigset, i)) {
				sig2str(i, signame);
				printf("%s SIG%s\n", str, signame);
			}
		}
	}
	errno = errno_save;
}

void
err_ret(char *msg)
{
	printf("%s\n", msg);
	return;
}

