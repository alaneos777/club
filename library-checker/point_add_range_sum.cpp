#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

template<typename T>
struct FenwickTree{
	int N;
	vector<T> bit;

	FenwickTree(const vector<T>& arr): N(arr.size()){
		bit.resize(N);
		for(int i = 0; i < N; ++i){
			bit[i] += arr[i];
			if((i | (i + 1)) < N)
				bit[i | (i + 1)] += bit[i];
		}
	}

	void update(int pos, T value){
		while(pos < N){
			bit[pos] += value;
			pos |= pos + 1;
		}
	}

	T query(int r){
		T res = 0;
		while(r >= 0){
			res += bit[r];
			r = (r & (r + 1)) - 1;
		}
		return res;
	}

	T query(int l, int r){
		return query(r) - query(l - 1);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<lli> a(n);
	for(lli& ai : a){
		cin >> ai;
	}
	FenwickTree<lli> ft(a);
	while(q--){
		int t;
		cin >> t;
		if(t == 0){
			int p, x;
			cin >> p >> x;
			ft.update(p, x);
		}else{
			int l, r;
			cin >> l >> r;
			--r;
			cout << ft.query(l, r) << "\n";
		}
	}
	return 0;
}