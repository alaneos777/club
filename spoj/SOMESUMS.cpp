#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;
const int M = 1e3 + 10;
vector<vector<lli>> A(M+1, vector<lli>(M+1));

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli inverse(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(abs(r0) == 1);
	if(r0 == -1) s0 = -s0;
	if(s0 < 0) s0 += m;
	return s0;
}

lli ncr(lli n, lli r){
	if(r < 0 || r > n) return 0;
	r = min(r, n - r);
	lli ans = 1;
	for(lli den = 1, num = n; den <= r; den++, num--)
		ans = ans * num % mod * inverse(den, mod) % mod;
	return ans;
}

lli lucas(lli m, lli n){
	lli ans = 1;
	do{
		lli mi = m % mod;
		lli ni = n % mod;
		ans = ans * ncr(mi, ni) % mod;
		m /= mod, n /= mod;
	}while(m != 0 || n != 0);
	return ans;
}

lli solve(int m, lli n, int k){
	if(m == 0) return powerMod(n, k);
	if(k == 0) return ncr(m + n, m);
	lli ans = 0;
	lli comb = lucas(k + m + n - 1, k + m);
	for(int i = 1; i <= k; ++i){
		ans += A[k][i-1] * comb % mod;
		if(ans >= mod) ans -= mod;
		if((k + m + n - i) % mod == 0) comb = lucas(k + m + n - i - 1, k + m);
		else comb = comb * (n - i) % mod * inverse(k + m + n - i, mod) % mod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int n = 1; n <= M; ++n){
		A[n][0] = 1;
		for(int m = 1; m < n; ++m){
			A[n][m] = (n - m) * A[n-1][m-1] % mod + (m + 1) * A[n-1][m] % mod;
			if(A[n][m] >= mod) A[n][m] -= mod;
		}
	}
	int t;
	cin >> t;
	while(t--){
		int m, k; lli n;
		cin >> m >> n >> k;
		cout << solve(m, n, k) << "\n";
	}
	return 0;
}