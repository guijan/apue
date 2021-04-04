#include <stdio.h>

int
main(void)
{
	const int word = 1;
	const char *byte = (char *)&word;

	printf("We're in a %s-endian machine, returning %d\n",
	    *byte ? "little" : "big", *byte);
	return (*byte);
}
