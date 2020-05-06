#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

const int M = 1.5e7;
vector<lli> acum(M+1, 1);

vector<int> sieve(int n){
	vector<int> lp(n+1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; ++i) lp[i] = (i&1 ? i : 2);
	for(int i = 3; i*i <= n; i += 2){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += 2*i){
				if(lp[j] == j) lp[j] = i;
			}
		}
	}
	return lp;
}

const auto lp = sieve(M);

int f(int n){
	int p = lp[n];
	while(n % p == 0) n /= p;
	return n == 1 ? p : 1;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int i = 2; i <= M; ++i){
		acum[i] = acum[i-1] * f(i) % mod;
	}
	int n, m;
	cin >> n >> m;
	lli ans = 1;
	int i = 1;
	while(i <= m && i <= n){
		int mi = m/i, ni = n/i;
		int u = min(m/mi, n/ni);
		ans = ans * powerMod(acum[u] % mod * powerMod(acum[i-1], mod-2) % mod, (lli)mi * ni) % mod;
		i = u + 1;
	}
	cout << ans << "\n";
	return 0;
}