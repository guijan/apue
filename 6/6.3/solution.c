#include <sys/utsname.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int
main(void)
{
	struct utsname *name;
	int retval = EXIT_FAILURE;
	errno = 0;
	if ((name = malloc(sizeof(struct utsname))) == NULL)
		goto err;
	if (uname(name) == -1)
		goto err;

	printf("%s %s %s %s %s\n", name->sysname, name->nodename,
		name->release, name->version, name->machine
	);

	retval = EXIT_SUCCESS;
err:
	free(name);
	if (errno)
		perror(NULL);
	return (retval);
}
