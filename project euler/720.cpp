#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct FenwickTree{
	int N;
	vector<int> bit;

	FenwickTree(int N): N(N){
		bit.resize(N);
	}

	void update(int pos, int value){
		while(pos < N){
			bit[pos] += value;
			pos |= pos + 1;
		}
	}

	int query(int r){
		int res = 0;
		while(r >= 0){
			res += bit[r];
			r = (r & (r + 1)) - 1;
		}
		return res;
	}
};

vector<int> ans(int n){
	vector<int> pi(n);
	iota(pi.begin(), pi.end(), 0);
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(pi[i], pi[j]);
	}
	return pi;
}

const int M = 1<<25;
const lli mod = 1e9 + 7;
int fact[M+1];

int order(const vector<int> & pi){
	int n = pi.size();
	int ans = 1;
	FenwickTree ft(n);
	for(int i = n-1, j = 0; i >= 0; --i, ++j){
		ans += (lli)ft.query(pi[i] - 1) * fact[j] % mod;
		if(ans >= mod) ans -= mod;
		ft.update(pi[i], 1);
	}
	return ans;
}

int main(){
	fact[0] = 1;
	for(lli i = 1; i <= M; ++i){
		fact[i] = i * fact[i-1] % mod;
	}
	vector<int> pi = ans(M);
	for(int i = 4; i < M; i += 4){
		swap(pi[i], pi[i-1]);
	}
	int pos = order(pi);
	cout << pos << "\n";
	return 0;
}