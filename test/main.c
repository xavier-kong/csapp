#include <stdio.h>

long test(long x) {
    x &= x >> 16;
    x &= x >> 8;
    x &= x >> 4;
    x &= x >> 2;

	printf("%06lX\n", (x));
    return (x & 1) == 1;
}

int main(void) {
	long x = 0xFFFFFFFFFFFf;
	printf("%06lX\n", (x));
	printf("%06lX\n", test(x));

}
