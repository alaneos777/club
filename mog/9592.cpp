#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

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
			if(i%p == 0){
				phi[d] = phi[i] * p;
				break;
			}else{
				phi[d] = phi[i] * (p-1);
			}
		}
	}
	return phi;
}

const int M = 1e6;
const auto phi = phiSieve(M);

vector<lli> PSmall(M+1);
map<int, lli> PBig;
lli P(int n){
	if(n <= M) return PSmall[n];
	if(PBig.count(n)) return PBig[n];
	lli ans = (lli)n*(n+1)/2;
	int i = 2;
	while(i <= n){
		int ni = n/i, nxt = n/ni;
		ans -= P(ni) * (nxt - (i-1));
		i = nxt+1;
	}
	return PBig[n] = ans;
}

int R(int n){
	lli ans = 1;
	int i = 2;
	while(i <= n){
		int ni = n/i, nxt = n/ni;
		ans = ans * power(ni, (P(nxt) - P(i-1)) % (mod-1)) % mod;
		i = nxt+1;
	}
	return ans*ans%mod*(n%mod)%mod;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int i = 1; i <= M; ++i){
		PSmall[i] = PSmall[i-1] + phi[i];
	}
	int n;
	cin >> n;
	cout << 2*P(n)-1 << " " << R(n) << "\n";
	return 0;
}