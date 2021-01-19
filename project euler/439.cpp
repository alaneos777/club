#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9;

auto muSieve(int n){
	vector<int> primes, lp(n+1), mu(n+1);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
			else{
				mu[d] = -mu[i];
			}
		}
	}
	return mu;
}

const lli N = 1e11;
const int limit = powl(N, 2.0/3.0);
const auto mu = muSieve(limit);

lli P(lli n){
	if(n & 1) return ((n+1)/2 % mod) * (n % mod) % mod;
	else return (n/2 % mod) * ((n+1) % mod) % mod;
}

lli F(lli n){
	lli ans = 0;
	lli m = sqrtl(n);
	for(lli i = 1, l = n/m; i <= l; ++i){
		ans += P(n/i);
		if(ans >= mod) ans -= mod;
	}
	for(lli i = 1; i < m; ++i){
		ans += (n/i - n/(i+1))%mod * P(i) % mod;
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

vector<int> USmall;
map<lli, int> UBig;
lli U(lli n){
	if(n < USmall.size()) return USmall[n];
	if(UBig.count(n)) return UBig[n];
	lli ans = 1;
	lli m = sqrtl(n);
	for(lli i = 2, l = n/m; i <= l; ++i){
		ans -= i*U(n/i) % mod;
		if(ans < 0) ans += mod;
	}
	for(lli i = 1; i < m; ++i){
		ans -= (P(n/i) - P(n/(i+1))) * U(i) % mod;
		if(ans < 0) ans += mod;
		if(ans >= mod) ans -= mod;
	}
	return UBig[n] = ans;
}

lli S(lli n){
	lli ans = 0;
	lli m = sqrtl(n);
	for(lli i = 1, l = n/m; i <= l; ++i){
		lli f2 = F(n/i);
		f2 = f2*f2 % mod;
		ans += i*mu[i] * f2 % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	for(lli i = 1; i < m; ++i){
		lli f2 = F(i);
		f2 = f2*f2 % mod;
		ans += (U(n/i) - U(n/(i+1))) * f2 % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	return ans;
}

int main(){
	USmall.resize(limit+1);
	for(int i = 1; i <= limit; ++i){
		USmall[i] = i*mu[i]%mod + USmall[i-1];
		if(USmall[i] >= mod) USmall[i] -= mod;
		if(USmall[i] < mod) USmall[i] += mod;
	}
	cout << S(N) << "\n";
	return 0;
}