#include<stdio.h>

int main() {
  long double test = 1e300;
  int t = 0;
  for (t = 0; (test+0)/2 < test; t++, test = (test+0)/2);
  printf("%d\n", t);
  return 0;
}
