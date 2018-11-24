#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli root(lli x){
	return floor(sqrt(x));
}

template<typename T>
struct SegmentTree{
	int N;
	vector<T> sum, maxi;

	SegmentTree(int N): N(N){
		sum.assign(N << 1, 0);
		maxi.assign(N << 1, 0);
	}

	void build(vector<T> & arr){
		for(int i = 0; i < N; ++i)
			sum[N + i] = maxi[N + i] = arr[i];
		for(int i = N - 1; i > 0; --i){
			sum[i] = sum[i << 1] + sum[i << 1 | 1];
			maxi[i] = max(maxi[i << 1], maxi[i << 1 | 1]);
		}
	}

	T max_query(int l, int r){
		T res = 0;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res = max(res, maxi[l++]);
			if(!(r & 1)) res = max(res, maxi[r--]);
		}
		return res;
	}

	void update(int l, int r){
		if(max_query(l, r) == 1) return;
		l += N, r += N;
		for(int i = l; i <= r; ++i)
			sum[i] = maxi[i] = root(sum[i]);
		l >>= 1, r >>= 1;
		while(l >= 1){
			for(int i = r; i >= l; --i){
				sum[i] = sum[i << 1] + sum[i << 1 | 1];
				maxi[i] = max(maxi[i << 1], maxi[i << 1 | 1]);
			}
			l >>= 1, r >>= 1;
		}
	}

	T sum_query(int l, int r){
		T res = 0;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res += sum[l++];
			if(!(r & 1)) res += sum[r--];
		}
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q, t, l, r, c = 1;
	while(cin >> n){
		vector<lli> arr(n);
		for(lli & a : arr)
			cin >> a;
		SegmentTree<lli> st(n);
		st.build(arr);
		cin >> q;
		cout << "Case #" << c++ << ":\n";
		while(q--){
			cin >> t >> l >> r;
			--l, --r;
			if(l > r) swap(l, r);
			if(t == 0){
				st.update(l, r);
			}else{
				cout << st.sum_query(l, r) << "\n";
			}
		}
		cout << "\n";
	}
	return 0;
}