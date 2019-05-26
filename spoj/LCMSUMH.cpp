#include <bits/stdc++.h>
using namespace std;
using lli = __int128;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const lli mod = 1e9 + 7;
 
lli gcd(lli a, lli b){
	lli r;
	while(b) r = a%b, a = b, b = r;
	return a;
}

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

const lli inv2 = powerMod(2, mod - 2, mod);

lli aleatorio(lli a, lli b){
	std::uniform_int_distribution<lli> dist(a, b);
	return dist(rng);
}

bool isPrime(lli n){
	if(n < 2) return false;
	if(n == 2) return true;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int i = 0; i < 32; ++i){
		lli a = aleatorio(1, n-1);
		lli m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) goto exit;
		for(int k = 0; k < s; ++k){
			m = m * m % n;
			if(m == n - 1) goto exit;
		}
		return false;
		exit:;
	}
	return true;
}

lli getFactor(lli n){
	lli a = aleatorio(1, n-1);
	lli b = aleatorio(1, n-1);
	lli x = 2, y = 2, d = 1;
	while(d == 1){
		x = x * (x + b) % n + a;
		y = y * (y + b) % n + a;
		y = y * (y + b) % n + a;
		d = gcd(x-y > 0 ? x-y : y-x, n);
	}
	return d;
}

map<lli, int> fact;
void factorize(lli n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrime(n)){
		lli f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorize(f, false);
		for(auto & it : fact){
			while(n % it.first == 0){
				n /= it.first;
				++it.second;
			}
		}
	}
	if(n > 1) ++fact[n];
}
 
lli lcmsum(lli n){
	lli ans = 1;
	factorize(n);
	for(auto par : fact){
		lli p; int k;
		tie(p, k) = par;
		if((p + 1) % mod == 0)
			ans = ans * (2*k + 1) % mod;
		else
			ans = ans * (powerMod(p, 2*k+1, mod) + 1) % mod * powerMod(p + 1, mod - 2, mod) % mod;
	}
	return (1 + ans) * n % mod * inv2 % mod;
}
 
int main(){
	ios_base::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--){
		long long int n;
		cin >> n;
		cout << (long long int)lcmsum(n) << "\n";
	}
	return 0;
}