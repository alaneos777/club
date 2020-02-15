#include <bits/stdc++.h>
using namespace std;

const int inf = 1e6;

struct SegmentTree{
	int N;
	vector<int> ST;

	SegmentTree(int N, vector<int> & arr): N(N){
		ST.resize(N << 1);
		for(int i = 0; i < N; ++i)
			ST[N + i] = arr[i];
		for(int i = N - 1; i > 0; --i)
			ST[i] = max(ST[i << 1], ST[i << 1 | 1]);
	}

	int query(int l, int r){
		int res = 0;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res = max(res, ST[l++]);
			if(!(r & 1)) res = max(res, ST[r--]);
		}
		return res;
	}

	int query(int l, int r, int x){
		int idx = inf, start = l;
		while(l <= r){
			int m = (l + r) / 2;
			if(query(start, m) >= x){
				idx = m;
				r = m-1;
			}else{
				l = m+1;
			}
		}
		return idx;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; ++i){
		cin >> a[i];
	}
	SegmentTree st(n, a);
	for(int i = 0; i < n; ++i){
		int j = min(n-1, i+a[i]);
		cout << min(st.query(i, j, a[i]+1), j+1) - (i+1) << " ";
	}
	cout << "\n";
	return 0;
}