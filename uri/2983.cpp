#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t, n;
	cin >> t;
	set<int> primes;
	while(t--){
		cin >> n;
		if(isPrime(n)) primes.insert(n);
	}
	cout << primes.size() << "\n";
	for(auto it = primes.begin(); it != primes.end(); ++it){
		if(it != primes.begin()) cout << ", ";
		cout << *it;
	}
	if(!primes.empty()) cout << ".";
	cout << "\n";
	return 0;
}