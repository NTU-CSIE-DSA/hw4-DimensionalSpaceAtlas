#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

const int MAXN = 1'000'000;
const int MAXT = 1'000'000;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int N = opt<int>("N");
	int T = opt<int>("T");
	const int MAXv = opt<int>("MAXv", 1'000'000'000);

	cout << N << ' ' << T << '\n';

	int w1 = opt<int>("w1", 1);
	int w2 = opt<int>("w2", 1);
	int w3 = opt<int>("w3", 1);
	
	for (int i = 1; i <= N; i++) {
		cout << (rnd.next(0, MAXv)) << " \n"[i==N];
	}
	int len = N;
	while (T--) {
		vector<int> operations;
		for (int i = 0; i < w2; i++) operations.push_back(2);
		if (len) {
			for (int i = 0; i < w1; i++) operations.push_back(1);
			for (int i = 0; i < w3; i++) operations.push_back(3);
		}
		assert(!operations.empty());
		int op = rnd.any(operations);
		cout << op << ' ';
		if (op == 1) {
			cout << rnd.next(1, len);
			len--;
		} else if (op == 2) {
			cout << rnd.next(0, len) << ' ' << rnd.next(0, MAXv);
			len++;
		} else if (op == 3) {
			int l = rnd.next(1, len);
			int r = rnd.next(l, len);
			cout << l << ' ' << r;
		}
		cout << '\n';
	}
	return 0;
}
