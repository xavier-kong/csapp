#include <stdio.h>


long isNotEqual(long x, long y) {
    return !!(x ^ y);
}

int main(void) {
  int n = 15;
  printf("%d", (~0) + (1 << n));
  printf("\n");
}
