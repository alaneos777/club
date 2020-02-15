#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool isPrime(lli n){
	if(n == 1) return false;
	for(lli d = 2; d*d <= n; ++d){
		if(n % d == 0) return false;
	}
	return true;
}

lli power(lli a, lli b, lli m){
	a %= m;
	if(a < 0) a += m;
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

lli f(lli n, int k, lli p){
	lli acum = 0;
	vector<lli> pol(k+2);
	for(int i = 0; i <= k+1; ++i){
		pol[i] = acum;
		acum += power(i+1, k, p);
		if(acum >= p) acum -= p;
	}
	if(n <= k+1) return pol[n];
	lli prod = 1;
	for(int i = 0; i <= k+1; ++i){
		prod = prod * (n%p - i) % p;
		if(prod < 0) prod += p;
	}
	if((k+1)%2 == 1) prod = (p - prod) % p;
	lli sum = 0;
	lli alt = 1;
	lli fact_a = 1, fact_b = 1;
	for(int i = 1; i <= k+1; ++i){
		fact_b = fact_b * i % p;
	}
	for(int i = 0; i <= k+1; ++i){
		assert((n%p - i) % p != 0);
		sum += pol[i] * alt % p * power(n - i, p-2, p) % p * power(fact_a, p-2, p) % p * power(fact_b, p-2, p) % p;
		if(sum >= p) sum -= p;
		alt = p - alt;
		fact_a = fact_a * (i + 1) % p;
		fact_b = fact_b * power(k+1-i, p-2, p) % p;
	}
	return sum * prod % p;
}

lli S(lli n, int k, lli p){
	n %= p;
	lli ans = (n+1)*f(n, k, p) % p - f(n, k+1, p);
	if(ans < 0) ans += p;
	return ans;
}

int main(){
	int n = 2e9;
	lli ans = 0;
	for(lli p = n; p <= n+2000; ++p){
		if(!isPrime(p)) continue;
		ans += S(lli(1e12), 10000, p);
	}
	cout << ans << "\n";
	return 0;
}