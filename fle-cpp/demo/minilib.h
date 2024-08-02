// As if this is the C standard library headers.

#include <stddef.h>
#include <sys/syscall.h>

long syscall(int num, ...);
size_t strlen(const char *s);
void print(const char *s, ...);
