#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

template<typename T>
struct SegmentTree{
	int N;
	vector<T> ST;

	SegmentTree(int N): N(N){
		ST.resize(N << 1);
	}

	//single element update in i
	void update(int i, T value){
		ST[i += N] = value; //update the element accordingly
		while(i >>= 1)
			ST[i] = ST[i << 1] + ST[i << 1 | 1];
	}

	//range query, [l, r]
	T query(int l, int r){
		if(l > r) return 0;
		T res = 0;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res += ST[l++];
			if(!(r & 1)) res += ST[r--];
		}
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, k, a, b, q;
	cin >> n >> k >> a >> b >> q;
	vector<lli> arr_a(n), arr_b(n);
	SegmentTree<lli> st_a(n), st_b(n);
	while(q--){
		int type;
		cin >> type;
		if(type == 1){
			int di, ai;
			cin >> di >> ai;
			di--;
			arr_a[di] = min(a, arr_a[di] + ai);
			arr_b[di] = min(b, arr_b[di] + ai);
			st_a.update(di, arr_a[di]);
			st_b.update(di, arr_b[di]);
		}else{
			int pi;
			cin >> pi;
			--pi;
			// [0, pi-1] [pi+k, n-1]
			cout << st_b.query(0, pi-1) + st_a.query(pi+k, n-1) << "\n";
		}
	}
	return 0;
}