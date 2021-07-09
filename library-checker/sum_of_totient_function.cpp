#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;
const lli inv_2 = (mod + 1) / 2;

auto phiSieve(int n){
	vector<int> primes, phi(n+1);
	vector<bool> is(n+1, true);
	phi[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(is[i]){
			primes.push_back(i);
			phi[i] = i-1;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0){
				phi[d] = phi[i] * p;
				break;
			}else{
				phi[d] = phi[i] * phi[p];
			}
		}
	}
	return phi;
}

vector<int> PSmall;
map<lli, int> Pbig;

int P(lli n){
	if(n < PSmall.size()) return PSmall[n];
	if(Pbig.count(n)) return Pbig[n];
	lli ans = (n % mod) * ((n+1) % mod) % mod * inv_2 % mod;
	lli i = 2;
	while(i <= n){
		lli ni = n/i, u = n/ni;
		ans -= (u - (i-1)) % mod * P(ni) % mod;
		if(ans < 0) ans += mod;
		i = u+1;
	}
	return Pbig[n] = ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n;
	cin >> n;
	int M = powl(n, 2.0/3.0);
	auto phi = phiSieve(M);
	PSmall.resize(M+1);
	for(int i = 1; i <= M; ++i){
		PSmall[i] = PSmall[i-1] + phi[i];
		if(PSmall[i] >= mod) PSmall[i] -= mod;
	}
	cout << P(n) << "\n";
	return 0;
}