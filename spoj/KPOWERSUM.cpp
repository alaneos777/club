#include <bits/stdc++.h>
using namespace std;
using lli = __int128;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

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

lli aleatorio(lli a, lli b){
	std::uniform_int_distribution<lli> dist(a, b);
	return dist(rng);
}

bool isPrime(lli n){
	if(n < 2) return false;
	if(n == 2) return true;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int i = 0; i < 16; ++i){
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

const lli mod = 1e9 + 7;

lli divs(lli n, lli k){
	lli ans = 1;
	factorize(n);
	for(auto par : fact){
		lli pk = powerMod(par.first, k, mod);
		if(pk == 1)
			ans = ans * (par.second + 1) % mod;
		else
			ans = ans * (powerMod(pk, par.second + 1, mod) - 1) % mod * powerMod(pk - 1, mod - 2, mod) % mod;
	}
	if(ans < 0) ans += mod;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	for(int i = 1; i <= t; ++i){
		long long int n, k;
		cin >> n >> k;
		cout << "Case " << i << ": " << (long long int)divs(n, k) << "\n";
	}
	return 0;
}