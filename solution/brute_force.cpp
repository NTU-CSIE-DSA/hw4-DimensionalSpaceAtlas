#include<stdio.h>

int a[(int)1e6+6];
int len;

void erase(int k) {
  for (int i = k; i < len; i++) a[i] = a[i+1];
  len--;
}

void insert(int k, int v) {
  for (int i = len; i > k; i--) a[i+1] = a[i];
  a[k+1] = v;
  len++;
}

long long sum(int l, int r) {
  long long rt = 0;
  for (int i = l; i <= r; i++) rt += a[i];
  return rt;
}

int main() {
  int N, T;
  scanf("%d%d", &N, &T);
  for (int i = 1; i <= N; i++) {
    scanf("%d", &a[i]);
    len++;
  }
  while (T--) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int k;
      scanf("%d", &k);
      erase(k);
    } else if (op == 2) {
      int k, b;
      scanf("%d%d", &k, &b);
      insert(k, b);
    } else if (op == 3) {
      int l, r;
      scanf("%d%d", &l, &r);
      printf("%lld\n", sum(l, r));
    }
  }
  printf("%d\n", len);
  for (int i = 1; i <= len; i++) {
    printf("%d%c", a[i], " \n"[i == len]);
  }
  return 0;
}
