#include <stdio.h>
#include <limits.h>

int
main(void)
{
	printf("%lu\n", (long)(INT_MAX / 100 / 60 / 60 / 24));
}
