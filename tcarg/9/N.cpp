#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli inf = 1e18;

template<typename T>
struct SegmentTree{
	int N;
	vector<T> maxi, mini;

	SegmentTree(int N): N(N){
		maxi.resize(N << 1, -inf);
		mini.resize(N << 1, inf);
	}

	void update(int i, T value){
		i += N;
		maxi[i] = value;
		mini[i] = value;
		while(i >>= 1){
			maxi[i] = max(maxi[i << 1], maxi[i << 1 | 1]);
			mini[i] = min(mini[i << 1], mini[i << 1 | 1]);
		}
	}

	T query(int l, int r){
		T mx = -inf;
		T mn = inf;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1){
				mx = max(mx, maxi[l]);
				mn = min(mn, mini[l]);
				l++;
			}
			if(!(r & 1)){
				mx = max(mx, maxi[r]);
				mn = min(mn, mini[r]);
				r--;
			}
		}
		return mx-mn;
	}
};


int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k, q;
	cin >> n >> k;
	vector<vector<lli>> pts(n, vector<lli>(k));
	for(int i = 0; i < n; ++i){
		for(lli& pi : pts[i]){
			cin >> pi;
		}
	}
	vector<SegmentTree<lli>> st(1<<(k-1), SegmentTree<lli>(n));
	auto update = [&](int pos, const vector<lli> & pt){
		for(int m = 0; m < (1<<(k-1)); ++m){
			lli sum = 0;
			for(int i = 0; i < k; ++i){
				if(m&(1<<i)){
					sum -= pt[i];
				}else{
					sum += pt[i];
				}
			}
			st[m].update(pos, sum);
		}
	};
	auto query = [&](int l, int r){
		lli ans = -inf;
		for(int m = 0; m < (1<<(k-1)); ++m){
			ans = max(ans, st[m].query(l, r));
		}
		return ans;
	};
	for(int i = 0; i < n; ++i){
		update(i, pts[i]);
	}
	cin >> q;
	while(q--){
		int t;
		cin >> t;
		if(t == 1){
			int pos;
			cin >> pos;
			--pos;
			vector<lli> pt(k);
			for(lli& pi : pt){
				cin >> pi;
			}
			update(pos, pt);
		}else{
			int l, r;
			cin >> l >> r;
		cout << query(l-1, r-1) << "\n";
		}
	}
	return 0;
}