#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
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
int64_t aleatorio(int64_t a, int64_t b){
	std::uniform_int_distribution<int64_t> dist(a, b);
	return dist(rng);
}
lli getFactor(lli n){
	lli a = aleatorio(1, n - 1), b = aleatorio(1, n - 1);
	lli x = 2, y = 2, d = 1;
	while(d == 1){
		x = x * ((x + b) % n) % n + a;
		y = y * ((y + b) % n) % n + a;
		y = y * ((y + b) % n) % n + a;
		d = __gcd(max(x - y, y - x), n);
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

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

lli phi(lli m){
	lli ans = m;
	factorizePollardRho(m);
	for(auto [p, _] : fact){
		ans -= ans/p;
	}
	return ans;
}

lli multiplicativeOrder(lli x, lli m){
	if(__gcd(x, m) != 1) return 0;
	lli order = phi(m);
	factorizePollardRho(order);
	for(auto [p, a] : fact){
		order /= power(p, a);
		lli tmp = powerMod(x, order, m);
		while(tmp != 1){
			tmp = powerMod(tmp, p, m);
			order *= p;
		}
	}
	return order;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int64_t a, m;
	cin >> a >> m;
	if(m == 1){
		cout << 1 << "\n";
		return 0;
	}
	a %= m;
	lli ans = multiplicativeOrder(a, m);
	if(ans == 0){
		cout << "Maradona e muito mais grande que o Pele\n";
	}else{
		cout << int64_t(ans) << "\n";
	}
	return 0;
}