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

	int kth(int l, int r, int k){
		if(l > r) return 0;
		if(lo == hi) return lo;
		int lb = freq[l - 1], rb = freq[r];
		int inLeft = rb - lb;
		if(k <= inLeft) return left->kth(lb + 1, rb, k);
		else return right->kth(l - lb, r - rb, k - inLeft);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for(int& ai : a){
		cin >> ai;
	}
	WaveletTree wt(a.begin(), a.end(), 0, 1e9);
	while(q--){
		int l, r, k;
		cin >> l >> r >> k;
		cout << wt.kth(l+1, r, k+1) << "\n";
	}
	return 0;
}