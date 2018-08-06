#include <bits/stdc++.h>
using namespace std;

struct WaveletTree{
	int lo, hi;
	WaveletTree *left, *right;
	vector<int> freq;

	//queries indexed in 1
	//build from [from, to) with non-negative values in range [x, y]
	WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y): lo(x), hi(y){
		if(lo == hi || from >= to) return;
		int m = (lo + hi) / 2;
		auto f = [m](int x){
			return x <= m;
		};
		freq.reserve(to - from + 1);
		freq.push_back(0);
		for(auto it = from; it != to; ++it)
			freq.push_back(freq.back() + f(*it));
		auto pivot = stable_partition(from, to, f);
		left = new WaveletTree(from, pivot, lo, m);
		right = new WaveletTree(pivot, to, m + 1, hi);
	}

	int lessThanOrEqual(int l, int r, int k){
		if(l > r || k < lo) return 0;
		if(hi <= k) return r - l + 1;
		int lb = freq[l - 1], rb = freq[r];
		return left->lessThanOrEqual(lb + 1, rb, k) + right->lessThanOrEqual(l - lb, r - rb, k);
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m, l, r, k;
	cin >> n;
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
	cin >> m;
	auto comp = [&](const pair<int, int>&a, const pair<int, int>&b){
		return a.first < b.first;
	};
	while(m--){
		cin >> l >> r >> k;
		auto pos = upper_bound(begin(values), end(values), make_pair(k, -(1 << 30)), comp);
		if(pos == end(values))
			cout << "0\n";
		else{
			--pos;
			cout << r - l + 1 - w.lessThanOrEqual(l, r, pos - begin(values)) << "\n";
		}
	}
	return 0;
}