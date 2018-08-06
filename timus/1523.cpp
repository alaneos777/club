#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 1e9;

template<typename T>
struct FenwickTree{
	int N;
	vector<T> bit;

	FenwickTree(int N){
		this->N = N;
		bit.assign(N, 0);
	}

	void update(int pos, T value){
		while(pos < N){
			bit[pos] = (bit[pos] + value) % mod;
			pos |= pos + 1;
		}
	}

	T query(int r){
		T res = 0;
		while(r >= 0){
			res = (res + bit[r]) % mod;
			r = (r & (r + 1)) - 1;
		}
		return res;
	}

	T query(int l, int r){
		return (query(r) - query(l - 1)) % mod;
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, k, a;
	cin >> n >> k;
	vector<FenwickTree<lli>> BIT(k - 1, FenwickTree<lli>(n + 1));
	lli count = 0;
	for(int i = 0; i < n; ++i){
		cin >> a;
		BIT[0].update(a, 1);
		for(int j = 1; j < k - 1; ++j){
			BIT[j].update(a, BIT[j - 1].query(a + 1, n));
		}
		count = (count + BIT[k - 2].query(a + 1, n)) % mod;
	}
	if(count < 0) count += mod;
	cout << count << "\n";
	return 0;
}