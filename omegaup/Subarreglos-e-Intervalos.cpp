#include <bits/stdc++.h>
using namespace std;

struct WaveletTree{
	int lo, hi;
	WaveletTree *left, *right;
	vector<int> freq;

	WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y): lo(x), hi(y){
		if(from >= to) return;
		int m = (lo + hi) / 2;
		auto f = [m](int x){return x <= m;};
		freq.reserve(to - from + 1);
		freq.push_back(0);
		for(auto it = from; it != to; ++it){
			freq.push_back(freq.back() + f(*it));
		}
		if(hi != lo){
			auto pivot = stable_partition(from, to, f);
			left = new WaveletTree(from, pivot, lo, m);
			right = new WaveletTree(pivot, to, m + 1, hi);
		}
	}

	int leq(int l, int r, int k){
		if(l > r || k < lo) return 0;
		if(hi <= k) return r - l + 1;
		int lb = freq[l - 1], rb = freq[r];
		return left->leq(lb + 1, rb, k) + right->leq(l - lb, r - rb, k);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, q, last = 0, l, r, a, b, L, R, A, B;
	cin >> n >> m >> q;
	vector<int> v(n);
	for(int & vi : v) cin >> vi;
	WaveletTree w(v.begin(), v.end(), 1, m + 10);
	while(q--){
		cin >> L >> R >> A >> B;
		l = (L + last) % n + 1;
		r = (R + last) % n + 1;
		a = (A + last) % m + 1;
		b = (B + last) % m + 1;
		if(l > r) swap(l, r);
		if(a > b) swap(a, b);
		cout << (last = w.leq(l, r, b) - w.leq(l, r, a - 1)) << "\n";
	}
	return 0;
}