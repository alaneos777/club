#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
 
lli gcd(lli a, lli b){
	lli r;
	while(b) r = a%b, a=b, b=r;
	return a;
}

lli extGcd(lli a, lli b, lli & x){
	lli q, r0 = a, r1 = b, ri, s0 = 1, s1 = 0, si;
	while(r1){
		q = r0 / r1;
		ri = r0 - r1 * q, r0 = r1, r1 = ri;
		si = s0 - s1 * q, s0 = s1, s1 = si;
	}
	x = s0;
	return r0;
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
 
lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}
 
vector<int> sieve(int n){
	vector<int> primes;
	vector<bool> isPrime(n+1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}
 
const vector<int> primes = sieve(1e5);
 
map<lli, int> factorize(lli n){
	map<lli, int> f;
	for(lli p : primes){
		if(p*p > n) break;
		int pot = 0;
		while(n % p == 0){
			n /= p;
			pot++;
		}
		if(pot) f[p] = pot;
	}
	if(n > 1) f[n] = 1;
	return f;
}
 
lli phi(lli n){
	auto f = factorize(n);
	lli ans = n;
	for(auto & p : f){
		ans -= ans / p.first;
	}
	return ans;
}
 
lli multiplicativeOrder(lli x, lli m){
	if(gcd(x, m) != 1) return 0;
	lli order = phi(m);
	auto f = factorize(order);
	for(auto & factor : f){
		lli p = factor.first;
		int a = factor.second;
		order /= power(p, a);
		lli tmp = powerMod(x, order, m);
		while(tmp != 1){
			tmp = powerMod(tmp, p, m);
			order *= p;
		}
	}
	return order;
}
 
lli discreteLogarithm(lli a, lli b, lli m){
	lli m1 = m, pw = 1, d, x;
	int nonRep = 0;
	while((d = gcd(a, m1)) > 1){
		if(pw == b) return nonRep;
		m1 /= d;
		++nonRep;
		pw = pw * a % m;
	}
	d = extGcd(pw, m, x);
	if(b % d > 0) return -1;
	b = x * (b / d) % m;
	if(b < 0) b += m;
	lli order = multiplicativeOrder(a, m1);
	lli n = sqrt(order) + 1;
	lli a_n = powerMod(a, n, m1);
	lli ans = 0;
	unordered_map<lli, lli> firstHalf;
	pw = a_n;
	for(lli p = 1; p <= n; p++){
		firstHalf[pw] = p;
		pw = (pw * a_n) % m1;
	}
	pw = b % m1;
	for(lli q = 0; q <= n; q++){
		if(firstHalf.count(pw)){
			lli p = firstHalf[pw];
			lli x = (n * p - q) % order;
			return x + nonRep;
		}
		pw = (pw * a) % m1;
	}
	return -1;
}

lli brute(lli a, lli b, lli m){
	for(lli x = 0; x < 2*m; ++x){
		if(powerMod(a, x, m)%m == b%m) return x;
	}
	return -1;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli x, z, k;
	while(cin >> x >> z >> k && !(x == 0 && z == 0 && k == 0)){
		lli ans = discreteLogarithm(x % z, k % z, z);
		if(ans == -1) cout << "No Solution\n";
		else cout << ans << "\n";
	}
	return 0;
}