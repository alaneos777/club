#include <bits/stdc++.h>
using namespace std;

vector<int> gp;
void sieve(int n){
	gp.resize(n + 1, 1);
	gp[0] = gp[1] = 0;
	for(int i = 2; i <= n; ++i) gp[i] = i;
	for(int i = 2; i <= n; i++)
		if(gp[i] == i)
			for(int j = i; j <= n; j += i)
				gp[j] = i;
}

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

	int lessThanOrEqual(int l, int r, int k){
		if(l > r || k < lo) return 0;
		if(hi <= k) return r - l + 1;
		int lb = freq[l - 1], rb = freq[r];
		return left->lessThanOrEqual(lb + 1, rb, k) + right->lessThanOrEqual(l - lb, r - rb, k);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	sieve(1e5);
	WaveletTree w(gp.begin() + 1, gp.end(), *min_element(gp.begin() + 1, gp.end()), *max_element(gp.begin() + 1, gp.end()));
	int q;
	cin >> q;
	while(q--){
		int n, k;
		cin >> n >> k;
		cout << w.lessThanOrEqual(2, n, k) << "\n";
	}
	return 0;
}