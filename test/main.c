#include <stdio.h>


long isNotEqual(long x, long y) {
    return !!(x ^ y);
}

int main(void) {
  long x = 1 << 3;
    printf("%6lX\n", x);
}
