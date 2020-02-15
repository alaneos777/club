#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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

const lli p = 1e9 + 7;

lli f(lli n, int k){
	n %= p;
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
		sum += pol[i] * alt % p * power(n - i, p-2, p) % p * power(fact_a, p-2, p) % p * power(fact_b, p-2, p) % p;
		if(sum >= p) sum -= p;
		alt = p - alt;
		fact_a = fact_a * (i + 1) % p;
		fact_b = fact_b * power(k+1-i, p-2, p) % p;
	}
	return sum * prod % p;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int k; lli n;
		cin >> n >> k;
		cout << f(n, k) << "\n";
	}
	return 0;
}