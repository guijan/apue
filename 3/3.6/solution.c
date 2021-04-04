#define _POSIX_C_SOURCE 200809L

#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void die(const char *const);

char *progname;

int
main(int argc, char *argv[])
{
	int fd;
	mode_t filemode = S_IRWXU;
	char upperalpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char cmpstr[] = "ABCDEFGHIJ";
	char testbuf[BUFSIZ];
	ssize_t bytes;

	progname = *argv;

	if (argc > 2)
		die("too many args");
	if ((fd = open(argv[1], O_RDWR | O_APPEND | O_CREAT, filemode)) == -1)
		die(NULL);

	if ((write(fd, upperalpha, strlen(upperalpha))) == -1)
		die(NULL);

	if ((lseek(fd, 0, SEEK_SET)) == -1)
		die("CAN'T SEEK");

	if ((bytes = read(fd, testbuf, 10)) == -1)
		die(NULL);
	else
		testbuf[10] = '\0';

	if (printf("%s\n", testbuf) < 0)
		die(NULL);

	if (strcmp(cmpstr, testbuf)) {
		if (printf("%s\n", "LSEEK'DnREAD STRINGS COMPARE EQUAL") < 0)
				die(NULL);
	} else {
		if (printf("%s\n", "LSEEK'DnREAD STRINGS COMPARE UNEQUAL") < 0)
				die(NULL);
	}

	if ((write(fd, "abcd", 4)) == -1)
		die(NULL);

	if (strncmp("abcd", testbuf, 4)) {
		if (printf("%s\n", "CAN'T SEEK TO START WITH APPEND FLAG") < 0)
				die(NULL);
	} else {
		if (printf("%s\n", "CAN SEEK TO START WITH APPEND FLAG") < 0)
				die(NULL);
	}

	if (printf("final string: %s\n", testbuf) < 0)
			die(NULL);

	exit(EXIT_SUCCESS);
}


void
die(const char *const msg)
{
	if (errno)
		perror(progname);
	if (msg != NULL)
		fprintf(stderr, "%s: %s\n", progname, msg);
	exit(EXIT_FAILURE);
}
