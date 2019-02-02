#include <bits/stdc++.h>
using namespace std;

struct WaveletTree{
	int lo, hi;
	WaveletTree *left, *right;
	vector<int> freq;

	//queries indexed in base 1, complexity for all queries: O(log(max_element))
	//build from [from, to) with non-negative values in range [x, y]
	//you can use vector iterators or array pointers
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

	//kth element in [l, r]
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
	vector<pair<int, int>> a(n);
	map<int, vector<int>> positions;
	for(int i = 0; i < n; ++i){
		cin >> a[i].first;
		positions[a[i].first].push_back(i);
		a[i].second = i;
	}
	sort(a.begin(), a.end());
	vector<int> arr(n);
	for(int i = 0; i < n; ++i){
		arr[a[i].second] = i;
	}
	WaveletTree wt(arr.begin(), arr.end(), 0, n-1);
	while(q--){
		int k, l, i;
		cin >> k >> i >> l;
		auto & tmp = positions[a[wt.kth(1, i+1, k)].first];
		if(l-1 < (int)tmp.size()){
			cout << tmp[l-1] << "\n";
		}else{
			cout << "-1\n";
		}
	}
	return 0;
}