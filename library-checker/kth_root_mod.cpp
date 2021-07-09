#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
using lli = long long int;

lli powerMod(lli a, lli b, lli mod){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
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

map<lli, int> fc;
void factorizePollardRho(lli n, bool clean = true){
	if(clean) fc.clear();
	while(n > 1 && !isPrimeMillerRabin(n)){
		lli f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorizePollardRho(f, false);
		for(auto & it : fc){
			while(n % it.first == 0){
				n /= it.first;
				++it.second;
			}
		}
	}
	if(n > 1) ++fc[n];
}

lli previous = -1;
auto fact(lli n){
	if(n != previous) factorizePollardRho(n);
	previous = n;
	return fc;
}

int findFirstGenerator(int p){
	int order = p - 1;
	auto f = fact(order);
	for(int x = 1; x < p; x++){
		if(__gcd(x, p) != 1) continue;
		bool test = true;
		for(auto[pr, _] : f){
			if(powerMod(x, order / pr, p) == 1){
				test = false;
				break;
			}
		}
		if(test) return x;
	}
	return -1; //not found
}

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash{
	int operator()(int x) const { return x ^ RANDOM; }
};

int discreteLogarithm(int g, int k, int b, int p){
	int a = powerMod(g, k, p);
	int order = (p-1) / __gcd(k, p-1);
	int n = sqrt(order) + 1;
	lli a_n = powerMod(a, n, p);
	gp_hash_table<int, int, chash> firstHalf;
	lli pw = a_n;
	for(int cnt = 1; cnt <= n; ++cnt, pw = pw * a_n % p){
		firstHalf[pw] = cnt;
	}
	pw = b;
	for(int q = 0; q <= n; ++q, pw = pw * a % p){
		if(firstHalf.find(pw) != firstHalf.end()) return (n * firstHalf[pw] - q) % order;
	}
	return -1;
}

tuple<lli, lli, lli> extgcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extgcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}

int discreteRoot(int k, int y, int m){
	if(y % m == 0) return 0;
	auto[d, x, _] = extgcd(k, m-1);
	if(d == 1){
		if(x < 0) x += m-1;
		return powerMod(y, x, m);
	}else{
		int g = findFirstGenerator(m);
		int t = discreteLogarithm(g, k, y, m);
		if(t == -1) return -1;
		return powerMod(g, t, m);
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int k, y, p;
		cin >> k >> y >> p;
		int x = 0;
		if(k == 0 && y == 0) x = -1;
		else if(k > 0 && y % p == 0) x = 0;
		else x = discreteRoot(k, y, p);
		cout << x << "\n";
	}
	return 0;
}