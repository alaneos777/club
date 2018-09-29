#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 700666007;

inline void modula(lli & n){
	while(n >= mod) n -= mod;
}

lli pow(lli b, lli e){
	lli ans = 1;
	while(e){
		if(e & 1) ans *= b;
		e >>= 1;
		b *= b;
	}
	return ans;
}

lli powMod(lli b, lli e, lli m){
	lli ans = 1;
	b %= m;
	while(e){
		if(e & 1) ans = (ans * b) % m;
		e >>= 1;
		b = (b * b) % m;
	}
	return ans;
}

lli gcd(lli a, lli b){
	lli r;
	while(b != 0) r = a % b, a = b, b = r;
	return a;
}

vector<int> primes;
void sieve(int n){
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i])
			primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
}

vector<pair<lli, int>> factorize(lli n){
	vector<pair<lli, int>> f;
	for(lli p : primes){
		if(p * p > n) break;
		int pot = 0;
		while(n % p == 0){
			pot++;
			n /= p;
		}
		if(pot) f.emplace_back(p, pot);
	}
	if(n > 1) f.emplace_back(n, 1);
	return f;
}

lli phi(lli n){
	lli ans = n;
	auto f = factorize(n);
	for(auto & factor : f)
		ans -= ans / factor.first;
	return ans;
}

lli multiplicativeOrder(lli x, lli m){
	lli order = phi(m);
	auto f = factorize(order);
	for(auto & factor : f){
		lli p = factor.first;
		int a = factor.second;
		order /= pow(p, a);
		lli tmp = powMod(x, order, m);
		while(tmp != 1){
			tmp = powMod(tmp, p, m);
			order *= p;
		}
	}
	return order;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	sieve(1e4);
	int t;
	cin >> t;
	while(t--){
		lli a, b, d, n;
		cin >> a >> b >> n;
		d = gcd(a, b);
		a /= d, b /= d;
		lli num = a, den = b;
		int dos = 0, cinco = 0;
		while(b % 2 == 0) dos++, b /= 2;
		while(b % 5 == 0) cinco++, b /= 5;
		int nonRepeatingLength = max(dos, cinco);
		int repeatingLength = multiplicativeOrder(10, b);
		vector<lli> nonRepeating(1), repeating(1);
		for(int i = 1; i <= nonRepeatingLength; ++i){
			nonRepeating.push_back(num * 10 / den);
			nonRepeating[i] += nonRepeating[i-1];
			modula(nonRepeating[i]);
			num = num * 10 % den;
		}
		for(int i = 1; i <= repeatingLength; ++i){
			repeating.push_back(num * 10 / den);
			repeating[i] += repeating[i-1];
			modula(repeating[i]);
			num = num * 10 % den;
		}
		lli ans = nonRepeating[min((lli)nonRepeatingLength, n)];
		n -= nonRepeatingLength;
		if(n > 0){
			lli howMany = (n / repeatingLength) % mod;
			lli res = n % repeatingLength;
			ans += repeating.back() * howMany % mod + repeating[res];
			modula(ans);
		}
		cout << ans << "\n";
	}
	return 0;
}