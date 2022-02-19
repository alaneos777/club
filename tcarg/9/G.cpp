#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

template<typename T>
struct FenwickTree{
	int N;
	vector<T> bit;

	FenwickTree(int N): N(N){
		bit.resize(N);
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
	FenwickTree<lli> bit(n+1);
	int l = 1, r = n;
	bool f = false;
	for(int i = 1; i <= n; ++i){
		bit.update(i, 1);
	}
	auto get = [&](int idx){
		if(!f) return l+idx-1;
		else return r-idx+1;
	};
	auto add = [&](int idx, int v){
		if(!f) return idx+v;
		else return idx-v;
	};
	while(q--){
		int t;
		cin >> t;
		if(t == 1){
			int p;
			cin >> p;
			if(2*p <= r-l+1){
				int idx = get(p+1);
				for(int i = get(p); l <= i && i <= r; i = add(i, -1)){
					bit.update(idx, bit.query(i, i));
					idx = add(idx, 1);
				}
				if(!f) l += p;
				else r -= p;
			}else{
				int idx = get(p);
				for(int i = get(p+1); l <= i && i <= r; i = add(i, 1)){
					bit.update(idx, bit.query(i, i));
					idx = add(idx, -1);
				}
				if(f){
					l += r-l+1-p;
					f = false;
				}else{
					r = p+l-1;
					f = true;
				}
			}
		}else{
			int a, b;
			cin >> a >> b;
			a = get(a+1), b = get(b);
			if(a > b) swap(a, b);
			cout << bit.query(a, b) << "\n";
		}
	}
	return 0;
}