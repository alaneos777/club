#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;

struct range{
	int l, r;
};

const int M = 1e5;
int col_f[51][M+1], col_g[51][M+1];
int mem_f[51][M+1], mem_g[51][M+1];

auto muSieve(int n){
	vector<int> mu(n+1), primes;
	vector<bool> is(n+1, true);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(is[i]){
			primes.push_back(i);
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
			else mu[d] = -mu[i];
		}
	}
	return mu;
}

const auto mu = muSieve(M);
int n, m, d = 1;
range ranges[M+1];

int f(int, int);
int g(int, int);

int f(int pos, int sum){
	if(pos == n) return 1;
	int& color = col_f[pos][sum];
	int& ans = mem_f[pos][sum];
	if(color == d) return ans;
	color = d, ans = 0;
	int l = (ranges[pos].l + d-1) / d, r = min(ranges[pos].r, m - sum*d) / d;
	if(l <= r){
		ans = g(pos+1, sum + r) - g(pos+1, sum + l-1);
		if(ans < 0) ans += mod;
	}
	return ans;
}

int g(int pos, int i){
	if(i < 0) return 0;
	int& color = col_g[pos][i];
	int& ans = mem_g[pos][i];
	if(color == d) return ans;
	color = d, ans = 0;
	ans = f(pos, i) + g(pos, i-1);
	if(ans >= mod) ans -= mod;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 0; i < n; ++i){
		cin >> ranges[i].l >> ranges[i].r;
	}
	int ans = 0;
	for(d = 1; d <= m; ++d){
		if(mu[d] == 0) continue;
		int term = f(0, 0);
		if(mu[d] == 1){
			ans += term;
			if(ans >= mod) ans -= mod;
		}else{
			ans -= term;
			if(ans < 0) ans += mod;
		}
	}
	cout << ans << "\n";
	return 0;
}