#include <bits/stdc++.h>
using namespace std;

struct WaveletTree{
	int lo, hi;
	WaveletTree *left, *right;
	vector<int> W;

	WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y): lo(x), hi(y){
		if(lo == hi || from >= to) return;
		int m = (lo + hi) / 2;
		auto f = [m](int x){
			return x <= m;
		};
		W.reserve(to - from + 1);
		W.push_back(0);
		for(auto it = from; it != to; ++it)
			W.push_back(W.back() + f(*it));
		auto pivot = stable_partition(from, to, f);
		left = new WaveletTree(from, pivot, lo, m);
		right = new WaveletTree(pivot, to, m + 1, hi);
	}

	int kth(int l, int r, int k){
		if(l > r) return 0;
		if(lo == hi) return lo;
		int lb = W[l - 1], rb = W[r];
		int inLeft = rb - lb;
		if(k <= inLeft) return left->kth(lb + 1, rb, k);
		else return right->kth(l - lb, r - rb, k - inLeft);
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m, l, r, k;
	cin >> n >> m;
	vector<pair<int, int>> values(n);
	vector<int> arr(n);
	for(int i = 0; i < n; ++i){
		cin >> values[i].first;
		values[i].second = i;
	}
	sort(begin(values), end(values));
	for(int i = 0; i < n; ++i){
		arr[values[i].second] = i;
	}
	WaveletTree w(begin(arr), end(arr), 0, n - 1);
	while(m--){
		cin >> l >> r >> k;
		cout << values[w.kth(l, r, k)].first << "\n";
	}
	return 0;
}