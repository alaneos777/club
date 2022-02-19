#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

template<typename T>
struct SegmentTree{
	int N;
	vector<T> ST;

	SegmentTree(vector<T> & arr): N(arr.size()){
		ST.resize(N << 1);
		for(int i = 0; i < N; ++i)
			ST[N + i] = arr[i];
		for(int i = N - 1; i > 0; --i)
			ST[i] = (ST[i << 1] & ST[i << 1 | 1]);
	}

	T query(int l, int r){
		T res = (1<<30)-1;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res &= ST[l++];
			if(!(r & 1)) res &= ST[r--];
		}
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<tuple<int,int,int>> conds;
	vector<vector<int>> ranges(30, vector<int>(n));
	while(m--){
		int l, r, q;
		cin >> l >> r >> q;
		--l, --r;
		conds.emplace_back(l, r, q);
		for(int b = 0; b < 30; ++b){
			if(q & (1<<b)){
				ranges[b][l]++;
				if(r+1 < n) ranges[b][r+1]--;
			}
		}
	}
	for(auto&range : ranges){
		partial_sum(range.begin(), range.end(), range.begin());
	}
	vector<int> arr;
	for(int i = 0; i < n; ++i){
		int ai = 0;
		for(int b = 29; b >= 0; --b){
			ai *= 2;
			if(ranges[b][i]) ai++;
		}
		arr.push_back(ai);
	}
	bool test = true;
	SegmentTree<int> st(arr);
	for(auto[l, r, q] : conds){
		if(st.query(l, r) != q){
			test = false;
			break;
		}
	}
	if(test){
		cout << "YES\n";
		for(int ai : arr){
			cout << ai << " ";
		}
		cout << "\n";
	}else{
		cout << "NO\n";
	}
	return 0;
}