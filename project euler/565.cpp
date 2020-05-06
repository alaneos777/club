#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli M = 1e11;
const int mod = 2017;
const int g = 5;

__int128 powerMod(__int128 a, __int128 b, __int128 m){
	__int128 ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

vector<bool> is;
vector<int> primes;
void sieve(int n){
	is.resize(n+1, true);
	is[0] = is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
}

vector<bool> isM;
void sieveM(){
	int sz = (M + 1) / mod;
	isM.resize(sz+1, true);
	for(int p : primes){
		if(p == mod) continue;
		lli step = mod * p;
		lli start = (mod - 1) * p % step * powerMod(p, mod - 2, mod) % step;
		// n = p*k = 2017*t - 1
		// n = 0 mod p
		// n = 2016 mod 2017
		// n = 2016 * inv(p, 2017) mod 2017p
		for(lli n = start; n <= M; n += step){
			isM[(n + 1) / mod] = false;
		}
	}
}

bool isPrime(lli n){
	if(n < is.size()){
		return is[n];
	}else if((n + 1) % mod == 0){
		return isM[(n + 1) / mod];
	}
	assert(0);
}

int main(){
	sieve(sqrt(M) + 1);
	sieveM();
	vector<lli> posible;
	for(int e = 1; (1ll << e) <= M; ++e){
		int cnt = __gcd(mod - 1, e + 1);
		int m = (mod - 1) / cnt;
		lli x1 = powerMod(g, m, mod);
		lli x = x1;
		for(int i = 1; i < cnt; ++i){
			lli p = x;
			if(p > 2 && p % 2 == 0) p += mod;
			for(; e * logl(p) <= logl(M); p += 2*mod){
				if(isPrime(p)){
					posible.push_back(power(p, e));
				}
			}
			x = x * x1 % mod;
		}
	}
	sort(posible.begin(), posible.end());
	cout << posible.size() << "\n";
	lli sum = 0;
	set<lli> st;
	for(lli x : posible){
		if(x == 1) continue;
		for(lli i = 1, y = x; y <= M; y += x, i++){
			if(__gcd(x, i) == 1){
				st.insert(y);
			}
		}
	}
	for(lli x : st){
		sum += x;
	}
	cout << sum << "\n";
	return 0;
}