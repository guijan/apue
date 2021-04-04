#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

void print_cloexec(void *fun);

int
main(int argc, char *argv[])
{
	DIR *dirp;
	struct dirent *direntp;
	if ((dirp = opendir("/")) == NULL)
		return EXIT_FAILURE;

	if (argc == 1) {
		print_cloexec(dirp);
		if (execlp("a.out", "a.out", "padding", (char *)0) == -1)
			return EXIT_FAILURE;
	}

	if ((direntp = readdir(dirp)) == NULL)
		return EXIT_FAILURE;

	print_cloexec(dirp);
}

void
print_cloexec(void *fun)
{
	fun = NULL;
}

