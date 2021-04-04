#if !defined(SOLUTION_H)
#define SOLUTION_H

#include <stddef.h>

int putenv_r(char **, char *);
size_t expandenv(size_t);

#endif
