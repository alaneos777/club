#include <bits/stdc++.h>
using namespace std;

vector<bool> sieve(int n){
	vector<int> primes;
	vector<bool> isPrime(n + 1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
	isPrime[0] = isPrime[1] = false;
	return isPrime;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	vector<bool> isPrime = sieve(2e6);
	while(cin >> n && n != 0){
		int l = n, r = n;
		while(!isPrime[l]) l--;
		while(!isPrime[r]) r++;
		cout << r-l << "\n";
	}
	return 0;
}