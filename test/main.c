#include <stdio.h>

long copyLSB(long x) {
	int lsb = x & 1;

	return -lsb;
}

int main(void) {
	printf("%li\n", copyLSB(7));
}
