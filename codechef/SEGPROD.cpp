#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int p;

template<typename T>
struct DisjointSparseTable{
	vector<vector<T>> left, right;
	int K, N;

	DisjointSparseTable(const vector<T> & arr){
		N = arr.size();
		K = log2(N) + 2;
		left.assign(K + 1, vector<T>(N));
		right.assign(K + 1, vector<T>(N));
		for(int j = 0; (1 << j) <= N; ++j){
			int mask = (1 << j) - 1;
			T acum = 1; //neutral element of your operation
			for(int i = 0; i < N; ++i){
				acum = (lli)acum * arr[i] % p; //your operation
				left[j][i] = acum;
				if((i & mask) == mask) acum = 1; //neutral element of your operation
			}
			acum = 1; //neutral element of your operation
			for(int i = N-1; i >= 0; --i){
				acum = (lli)acum * arr[i] % p; //your operation
				right[j][i] = acum;
				if((i & mask) == 0) acum = 1; //neutral element of your operation
			}
		}
	}

	T query(int l, int r){
		if(l == r) return left[0][l];
		int i = 31 - __builtin_clz(l^r);
		return (lli)left[i][r] * right[i][l] % p; //your operation
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n, q;
		cin >> n >> p >> q;
		vector<int> a(n);
		for(int& ai : a){
			cin >> ai;
			ai %= p;
		}
		int sz = q/64 + 2;
		vector<int> b(sz);
		for(int& bi : b){
			cin >> bi;
		}
		DisjointSparseTable<int> ds(a);
		int x = 0, prevL = 0, prevR = 0;
		for(int i = 0; i < q; ++i){
			int l, r;
			if((i & 63) == 0){
				l = (b[i>>6] + x) % n;
				r = (b[(i>>6)+1] + x) % n;
			}else{
				l = (prevL + x) % n;
				r = (prevR + x) % n;
			}
			if(l > r) swap(l, r);
			x = (ds.query(l, r) + 1) % p;
			prevL = l, prevR = r;
		}
		cout << x%p << "\n";
	}
	return 0;
}