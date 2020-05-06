#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;
const lli inv_2 = (mod + 1) / 2;
const lli N = 1e11;
const int limit = pow(N, 2.0/3.0);

inline lli comb_2(lli n){
	n %= mod;
	return n * (n-1) % mod * inv_2 % mod;
}

auto muSieve(int n){
	vector<int> mu(n+1, -1);
	mu[0] = 0, mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(mu[i]){
			for(int j = 2*i; j <= n; j += i){
				mu[j] -= mu[i];
			}
		}
	}
	return mu;
}

const auto mu = muSieve(limit);
vector<lli> USmall(limit + 1);

map<lli, lli> UBig;
lli U(lli n){
	if(n <= limit) return USmall[n];
	if(UBig.count(n)) return UBig[n];
	lli ans = 1;
	lli m = sqrt(n);
	for(lli i = 2, l = n/m; i <= l; ++i){
		ans -= U(n/i);
		if(ans < 0) ans += mod;
	}
	for(lli i = 1; i < m; ++i){
		ans -= (n/i - n/(i+1)) * U(i) % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	return UBig[n] = ans;
}

int main(){
	for(int i = 1; i <= limit; ++i){
		USmall[i] = USmall[i-1] + mu[i];
		if(USmall[i] < 0) USmall[i] += mod;
		if(USmall[i] >= mod) USmall[i] -= mod;
	}
	lli ans = 0;
	lli p_pow = 2;
	while(p_pow <= N){
		lli n = N / p_pow;
		lli i = 1;
		while(i <= n){
			lli ni = n / i;
			lli u = n / ni;
			ans += (U(u) - U(i-1)) * comb_2(ni) % mod;
			if(ans < 0) ans += mod;
			if(ans >= mod) ans -= mod;
			i = u + 1;
		}
		p_pow <<= 1;
	}
	cout << ans << "\n";
	return 0;
}