#include<bits/stdc++>
using namespace std;

const int MAXN = 1e6+6;
int a[MAXN];
int len;

void delete(int k) {
  for (int i = k; i < len; i++) a[i] = a[i+1];
  len--;
}

void insert(int k, int v) {
  for (int i = len; i >= k; i--) a[i+1] = a[i];
  a[k] = v;
  len++;
}

long long sum(int l, int r) {
  long long rt = 0;
  for (int i = l; i <= r; i++) rt += a[i];
  return rt;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int N, T;
  cin >> N >> T;
  for (int i = 1; i <= N; i++) {
    cin >> a[i];
    len++;
  }
  while (T--) {
    int op;
    cin >> op;
    if (op == 1) {
      int k;
      cin >> k;
      delete(k);
    } else if (op == 2) {
      int k, b;
      cin >> k >> b;
      insert(k, b);
    } else if (op == 3) {
      int l, r;
      cin >> l >> r;
      cout << sum(l, r) << '\n';
    }
  }
  cout << len << '\n';
  for (int i = 1; i <= len; i++) {
    cout << i << " \n"[i == len];
  }
  return 0;
}
