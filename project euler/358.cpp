#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

__int128_t powerMod(__int128_t a, __int128_t b, __int128_t m){
	__int128_t ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

bool isPrime(lli n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		__int128_t m = powerMod(a, d, n);
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
lli getFactor(__int128_t n){
	__int128_t a = aleatorio(1, n - 1), b = aleatorio(1, n - 1);
	__int128_t x = 2, y = 2, d = 1;
	while(d == 1){
		x = x * (x + b) % n + a;
		y = y * (y + b) % n + a;
		y = y * (y + b) % n + a;
		d = __gcd(abs(x - y), n);
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

auto getPrimes(int n){
	vector<int> st;
	factorize(n);
	for(auto [p, a] : fact){
		st.push_back(p);
	}
	return st;
}

bool isPrimitiveRoot(int p){
	if(p == 2 || p == 5) return false;
	for(int pi : getPrimes(p-1)){
		if(powerMod(10, (p-1) / pi, p) == 1) return false;
	}
	return true;
}

bool startsWith(int p, const string & pattern){
	int ten = 1;
	string leftmost;
	for(int i = 0; i < p-1 && i < pattern.size(); ++i){
		int d = ten*10ll/p;
		leftmost += char(d+'0');
		ten = ten * 10ll % p;
	}
	return leftmost == pattern;
}

int main(){
	int rightmost = 56789;
	int inv = 100000 - powerMod(rightmost, 40000-1, 100000);
	for(int p = inv; ;p += 100000){
		if(isPrime(p) && isPrimitiveRoot(p) && startsWith(p, "00000000137")){
			cout << p << "\n";
			cout << 9ll*(p-1)/2 << "\n";
			break;
		}
	}
	return 0;
}