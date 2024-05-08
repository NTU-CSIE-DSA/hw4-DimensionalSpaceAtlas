#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int N = opt<int>("N", 1'000'000);
	int T = opt<int>("T", 1'000'000);
	const int max_v = opt<int>("max_v", 1'000'000'000);
	const int min_v = opt<int>("min_v", 0);
	const int max_len = opt<int>("max_len", 10'000'000);
	const int min_len = opt<int>("min_len", 0);
	const int final_len = opt<int>("final_len", -1);
	int w1 = opt<int>("w1", 1);
	int w2 = opt<int>("w2", 1);
	int w3 = opt<int>("w3", 1);
	int n_ins_p = opt<int>("n_ins_p", -1);
	int ins_p = opt<int>("ins_p", -1);
	int del_p = opt<int>("del_p", -1);

	if (ins_p != -1) n_ins_p = -1;

	assert(max_len >= N);
	assert(max_len >= min_len);
	assert(final_len == -1 || (min_len <= final_len && final_len <= max_len));
	assert(n_ins_p);
	assert(del_p);

	set<int> s_ins_ps;
	if (n_ins_p != -1) while (s_ins_ps.size() < n_ins_p) s_ins_ps.insert(rnd.next(0, N));
	vector<int> v_ins_ps = vector<int>(s_ins_ps.begin(), s_ins_ps.end());
	stack<int> nv_ins_ps;

	cout << N << ' ' << T << '\n';
	for (int i = 1; i <= N; i++) {
		cout << (rnd.next(min_v, max_v)) << " \n"[i==N];
	}
	int len = N;
	while (T--) {
		assert(final_len == -1 || abs(final_len - len) <= T+1);
		vector<int> operations;
		if (final_len == -1 || abs(final_len - len) < T+1) {
			if (len < max_len && (final_len == -1 || len+1 - final_len < T)) 
				for (int i = 0; i < w2; i++) operations.push_back(2);
			if (len > min_len && (final_len == -1 || final_len - (len-1) < T))
				for (int i = 0; i < w1; i++) operations.push_back(1);
			if (len) for (int i = 0; i < w3; i++) operations.push_back(3);
		} else {
			if (len < final_len) operations.push_back(2);
			else if (len > final_len) operations.push_back(1);
			else assert(0);
		}
		assert(!operations.empty());
		int op = rnd.any(operations);
		cout << op << ' ';
		if (op == 1) {
			if (del_p != -1) cout << min(del_p, len);
			else cout << rnd.next(1, len);
			len--;
			if (n_ins_p != -1 && v_ins_ps.size() && *v_ins_ps.rbegin() > len) {
				nv_ins_ps.push(*v_ins_ps.rbegin());
				v_ins_ps.pop_back();
			}
		} else if (op == 2) {
			if (ins_p != -1) cout << min(ins_p, len) << ' ' << rnd.next(min_v, max_v);
			else if (n_ins_p != -1) {
				if (v_ins_ps.size()) cout << rnd.any(v_ins_ps) << ' ' << rnd.next(min_v, max_v);
				else cout << rnd.next(0, len) << ' ' << rnd.next(min_v, max_v);
			} else cout << rnd.next(0, len) << ' ' << rnd.next(min_v, max_v);
			len++;
			if (n_ins_p != -1 && !nv_ins_ps.empty() && nv_ins_ps.top() <= len) {
				v_ins_ps.push_back(nv_ins_ps.top());
				nv_ins_ps.pop();
			}
		} else if (op == 3) {
			int l = rnd.next(1, len);
			int r = rnd.next(l, len);
			cout << l << ' ' << r;
		}
		cout << '\n';
	}
	return 0;
}
