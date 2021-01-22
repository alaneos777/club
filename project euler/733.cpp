#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

struct FenwickTree{
	int N;
	vector<int> bit;

	FenwickTree(int N): N(N){
		bit.resize(N);
	}

	void update(int pos, int value){
		while(pos < N){
			bit[pos] += value;
			if(bit[pos] >= mod) bit[pos] -= mod;
			pos |= pos + 1;
		}
	}

	int query(int r){
		int res = 0;
		while(r >= 0){
			res += bit[r];
			if(res >= mod) res -= mod;
			r = (r & (r + 1)) - 1;
		}
		return res;
	}

	int query(int l, int r){
		lli ans = query(r) - query(l - 1);
		if(ans < 0) ans += mod;
		return ans;
	}
};

int main(){
	int N = 1e6;
	vector<int> a(N);
	a[0] = 153;
	for(int i = 1; i < N; ++i){
		a[i] = 153ll * a[i-1] % 10000019;
	}
	int M = *max_element(a.begin(), a.end());
	int k = 4;
	vector<FenwickTree> bit(k-1, FenwickTree(M+1)), sum(k-1, FenwickTree(M+1));
	lli ans = 0;
	for(int i = 0; i < N; ++i){
		bit[0].update(a[i], 1);
		sum[0].update(a[i], a[i]);
		for(int j = 1; j < k-1; ++j){
			int cnt = bit[j-1].query(0, a[i] - 1);
			bit[j].update(a[i], cnt);
			sum[j].update(a[i], ((lli)a[i] * cnt + sum[j-1].query(0, a[i] - 1)) % mod);
		}
		ans += ((lli)a[i] * bit[k-2].query(0, a[i] - 1) + sum[k-2].query(0, a[i] - 1)) % mod;
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}