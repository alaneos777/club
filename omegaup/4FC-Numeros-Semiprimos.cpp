#include <bits/stdc++.h>
using namespace std;

vector<int> linearPrimeSieve(int n){
	vector<int> primes;
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
	return primes;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n = 1e5;
	vector<int> primes = linearPrimeSieve(n);
	vector<bool> semi(n+1);
	for(int i = 0; i < primes.size(); ++i){
		for(int j = i + 1; j < primes.size(); ++j){
			long long int x = (long long int)primes[i] * primes[j];
			if(x > n) break;
			semi[x] = true;
		}
	}
	for(int i = 2; i <= n; ++i){
		if(semi[i]) cout << i << "\n";
	}
	return 0;
}