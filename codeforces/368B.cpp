#include <bits/stdc++.h>
using namespace std;

const int M = 1e5 + 10;
const int inf = numeric_limits<int>::max();

struct SegmentTree{
	int N;
	vector<vector<int>> ST;

	SegmentTree(int N, vector<int> & arr): N(N){
		ST.resize(N << 1);
		for(int i = 0; i < N; ++i)
			ST[N + i].push_back(arr[i]);
		for(int i = N - 1; i > 0; --i){
			merge(ST[i << 1].begin(), ST[i << 1].end(), ST[i << 1 | 1].begin(), ST[i << 1 | 1].end(), back_inserter(ST[i]));
		}
	}

	int query(int l, int r, int k){
		int res = 0;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1){
				res += (int)ST[l].size() - (upper_bound(ST[l].begin(), ST[l].end(), k) - ST[l].begin());
				l++;
			}
			if(!(r & 1)){
				res += (int)ST[r].size() - (upper_bound(ST[r].begin(), ST[r].end(), k) - ST[r].begin());
				r--;
			}
		}
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, l;
	cin >> n >> m;
	vector<int> a(n);
	for(int & ai : a) cin >> ai;
	vector<int> last(M+1, inf);
	vector<int> next(n, inf);
	for(int i = n-1; i >= 0; --i){
		if(last[a[i]] != inf) next[i] = last[a[i]];
		last[a[i]] = i;
	}
	SegmentTree st(n, next);
	while(m--){
		cin >> l;
		cout << st.query(l-1, n-1, n-1) << "\n";
	}
	return 0;
}