#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

uint64_t mult(uint64_t a, uint64_t b, uint64_t m){
	if(a >= m) a %= m;
	if(b >= m) b %= m;
	uint64_t c = (long double)a * b / m;
	int64_t r = (int64_t)(a * b - c * m) % (int64_t)m;
	return r < 0 ? r + m : r;
}

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = mult(ans, a, m);
		b >>= 1;
		a = mult(a, a, m);
	}
	return ans % m;
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
			m = mult(m, m, n);
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
		x = mult(x, x + b, n) + a;
		y = mult(y, y + b, n) + a;
		y = mult(y, y + b, n) + a;
		d = __gcd(abs(x - y), n);
	}
	return d;
}

map<lli, int> fact;
void factorizePollardRho(lli n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrimeMillerRabin(n)){
		lli f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorizePollardRho(f, false);
		for(auto & it : fact){
			while(n % it.first == 0){
				n /= it.first;
				++it.second;
			}
		}
	}
	if(n > 1) ++fact[n];
}

bool isPower(lli n){
	factorizePollardRho(n);
	return fact.size() == 1 && fact.begin()->first % 2 == 1;
}

bool has(lli n){
	if(n == 1) return false;
	if(n == 2 || n == 4) return true;
	if(n % 2 == 0){
		return isPower(n / 2);
	}else{
		return isPower(n);
	}
}

lli brute(lli n){
	lli ans = 1;
	for(lli i = 1; i <= n; ++i){
		if(__gcd(i, n) == 1) ans = ans * i % n;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli m;
	cin >> m;
	//cout << brute(m) << " ";
	if(has(m)){
		cout << (m - 1) % m << "\n";
	}else{
		cout << 1 % m << "\n";
	}
	return 0;
}