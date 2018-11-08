#include <bits/stdc++.h>
using namespace std;

const int inf = numeric_limits<int>::max();

template<typename T>
struct DisjointSparseTable{
	vector<vector<T>> left, right;
	int K, N;

	DisjointSparseTable(vector<T> & arr){
		N = arr.size();
		K = log2(N) + 2;
		left.assign(K + 1, vector<T>(N));
		right.assign(K + 1, vector<T>(N));
		for(int j = 0; (1 << j) <= N; ++j){
			int mask = (1 << j) - 1;
			T acum = inf; //neutral element of your operation
			for(int i = 0; i < N; ++i){
				acum = min(acum, arr[i]); //your operation
				left[j][i] = acum;
				if((i & mask) == mask) acum = inf; //neutral element of your operation
			}
			acum = inf; //neutral element of your operation
			for(int i = N-1; i >= 0; --i){
				acum = min(acum, arr[i]); //your operation
				right[j][i] = acum;
				if((i & mask) == 0) acum = inf; //neutral element of your operation
			}
		}
	}

	T query(int l, int r){
		if(l == r) return left[0][l];
		int i = 31 - __builtin_clz(l^r);
		return min(left[i][r], right[i][l]); //your operation
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q, l, r;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	cin >> q;
	DisjointSparseTable<int> dsp(a);
	while(q--){
		cin >> l >> r;
		cout << dsp.query(l, r) << "\n";
	}
	return 0;
}