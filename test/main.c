#include <stdio.h>

long test(long x) {
	printf("THE CAHR %06lx\n", x);
	unsigned int ODD_BITS = 0xAAAAAAAA;
	printf("WHAT %06lX", (x & ODD_BITS));

	return (x & ODD_BITS) == ODD_BITS;

}

int main(void) {
	printf("%06lX\n", test(0xAAAA));

}
