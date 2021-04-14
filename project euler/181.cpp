#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
const lli mod1 = 1e9 + 7;
const lli mod2 = 1e9 + 9;

void gen_partitions(int n, function<void(const vector<int>&)> f){
	vector<int> a(n);
	int k = 1, y = n-1;
	while(k != 0){
		int x = a[k-1] + 1;
		k--;
		while(2*x <= y){
			a[k] = x;
			y -= x;
			k++;
		}
		int l = k+1;
		while(x <= y){
			a[k] = x;
			a[l] = y;
			f(vector<int>(a.begin(), a.begin() + k+2));
			x++;
			y--;
		}
		a[k] = x+y;
		y = x+y-1;
		f(vector<int>(a.begin(), a.begin() + k+1));
	}
}

template<lli mod>
lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

using poly = vector<int>;

template<lli mod>
poly mult(const poly & a, const poly & b, int sz){
	poly c(min(sz, int(a.size() + b.size() - 1)));
	for(int i = 0; i < a.size() && i < sz; ++i){
		for(int j = 0; j < b.size() && j < sz; ++j){
			if(i+j >= sz) break;
			c[i+j] += (lli)a[i]*b[j] % mod;
			if(c[i+j] >= mod) c[i+j] -= mod;
		}
	}
	return c;
}

template<lli mod>
poly inverse(const poly & a, int sz){
	lli inv_a0 = power<mod>(a[0], mod-2);
	poly b(sz);
	b[0] = inv_a0;
	for(int i = 1; i < sz; ++i){
		for(int j = 1; j <= i && j < a.size(); ++j){
			b[i] -= (lli)a[j]*b[i-j] % mod;
			if(b[i] < 0) b[i] += mod;
		}
		b[i] = b[i] * inv_a0 % mod;
	}
	return b;
}

template<lli mod>
lli solve(int B, int W){
	int N = B+W;

	vector<int> fact(N+1, 1);
	for(lli i = 2; i <= N; ++i){
		fact[i] = i*fact[i-1] % mod;
	}
	vector<vector<int>> ncr(N+1, vector<int>(N+1));
	for(int i = 0; i <= N; ++i){
		ncr[i][0] = ncr[i][i] = 1;
		for(int j = 1; j < i; ++j){
			ncr[i][j] = (ncr[i-1][j-1] + ncr[i-1][j]) % mod;
		}
	}

	lli ans = 0;
	int cnt = 0;
	gen_partitions(N, [&](const vector<int>& part){
		cnt++;
		if(cnt % 10000 == 0) cout << cnt << "\n";
		vector<int> c(N+1);
		for(int p : part){
			c[p]++;
		}
		lli coef = 1;
		for(int i = 1; i <= N; ++i){
			coef = coef * power<mod>(i, c[i]) % mod * fact[c[i]] % mod;
		}
		coef = power<mod>(coef, mod-2);
		int sz = max(B,W)+1;
		poly P = {1};
		for(int i = 1; i <= N; ++i){
			if(c[i] == 0) continue;
			poly curr(i*c[i]+1);
			for(int j = 0; j <= c[i]; ++j){
				curr[i*j] = ncr[c[i]][j];
				if(j & 1) curr[i*j] = mod - curr[i*j];
			}
			P = mult<mod>(P, curr, sz);
		}
		P = inverse<mod>(P, sz);
		coef = coef * P[B] % mod * P[W] % mod;
		ans += coef;
		if(ans >= mod) ans -= mod;
	});

	return ans;
}

int main(){
	int B = 60, W = 40;
	lli a1 = solve<mod1>(B, W);
	cout << a1 << "\n";
	lli a2 = solve<mod2>(B, W);
	cout << a2 << "\n";
	lli x1 = a1;
	lli x2 = (a2 - x1) % mod2 * power<mod2>(mod1 % mod2, mod2 - 2) % mod2;
	if(x2 < 0) x2 += mod2;
	lli ans = x1 + x2*mod1;
	cout << ans << "\n";
	return 0;
}