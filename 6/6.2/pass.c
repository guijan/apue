#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(void)
{
	struct passwd *pass;
	int retval = EXIT_FAILURE;

	errno = 0;
	if ((pass = getpwnam_shadow("jan")))
		printf("Encrypted password: %s\n", pass->pw_passwd);

	if (errno == 0)
		retval = EXIT_SUCCESS;
	else
		perror(NULL);

	endpwent();
	return (retval);
}
