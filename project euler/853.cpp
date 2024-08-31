#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

bool isPrimeMillerRabin(lli n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		lli m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) continue;
		int k = 0;
		for(; k < s; ++k){
			m = m * m % n;
			if(m == n - 1) break;
		}
		if(k == s) return false;
	}
	return true;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
lli aleatorio(lli a, lli b){
	std::uniform_int_distribution<lli> dist(a, b);
	return dist(rng);
}
lli getFactor(lli n){
	lli a = aleatorio(1, n - 1), b = aleatorio(1, n - 1);
	lli x = 2, y = 2, d = 1;
	while(d == 1){
		x = x * ((x + b) % n) % n + a;
		y = y * ((y + b) % n) % n + a;
		y = y * ((y + b) % n) % n + a;
		d = gcd(abs(x - y), n);
	}
	return d;
}

map<lli, int> fact;
void factorizeRho(lli n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrimeMillerRabin(n)){
		lli f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorizeRho(f, false);
		for(auto&[p, a] : fact){
			while(n % p == 0){
				n /= p;
				++a;
			}
		}
	}
	if(n > 1) ++fact[n];
}

auto factorize(lli n){
	factorizeRho(n);
	vector<pair<lli, int>> f;
	for(auto[p, a] : fact){
		f.emplace_back(p, a);
	}
	return f;
}

auto getDivs(lli n){
	set<lli> divs;
	auto f = factorize(n);
	function<void(lli, int)> dfs = [&](lli acum, int pos){
		if(pos == f.size()){
			divs.insert(acum);
		}else{
			auto[p, a] = f[pos];
			lli p_pow = 1;
			for(int i = 0; i <= a; ++i){
				dfs(acum * p_pow, pos+1);
				p_pow *= p;
			}
		}
	};
	dfs(1, 0);
	return divs;
}

int main(){
	int n = 120, L = 1e9;
	vector<lli> F(n+1);
	F[0] = 0, F[1] = 1;
	for(int i = 2; i <= n; ++i){
		F[i] = F[i-1] + F[i-2];
	}
	auto divs = getDivs(__gcd(F[n], F[n-1]-1));
	for(int d : getDivs(n)){
		if(d == n) continue;
		auto divsToRemove = getDivs(__gcd(F[d], F[d-1]-1));
		for(lli x : divsToRemove){
			divs.erase(x);
		}
	}
	lli sum = 0;
	for(lli d : divs){
		if(d < L) sum += d;
	}
	cout << (int64_t)sum << "\n";
	return 0;
}