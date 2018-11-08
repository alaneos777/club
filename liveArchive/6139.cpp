#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct SegmentTree{
	int N;
	vector<T> ST;

	SegmentTree(int N): N(N){
		ST.assign(N << 1, 0);
	}

	void build(){
		for(int i = N - 1; i > 0; --i)
			ST[i] = ST[i << 1] * ST[i << 1 | 1];
	}

	void update(int i, T value){
		ST[i += N] = value;
		while(i >>= 1)
			ST[i] = ST[i << 1] * ST[i << 1 | 1];
	}

	T query(int l, int r){
		T res = 1;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res *= ST[l++];
			if(!(r & 1)) res *= ST[r--];
		}
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	while(cin >> n >> k){
		SegmentTree<int> st(n);
		for(int i = n; i < 2*n; ++i){
			cin >> st.ST[i];
			if(st.ST[i] > 0) st.ST[i] = 1;
			else if(st.ST[i] < 0) st.ST[i] = -1;
		}
		st.build();
		char action;
		int i, j;
		while(k--){
			cin >> action >> i >> j;
			if(action == 'C'){
				if(j > 0) j = 1;
				else if(j < 0) j = -1;
				st.update(i - 1, j);
			}else{
				int res = st.query(i - 1, j - 1);
				if(res > 0) cout << "+";
				else if(res < 0) cout << "-";
				else cout << "0";
			}
		}
		cout << "\n";
	}
	return 0;
}