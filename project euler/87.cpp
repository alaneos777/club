#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> sieve(int n){
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

const int N = 50000000-1;

int main(){
	vector<int> primes = sieve(sqrt(N) + 10);
	vector<int> A, B, C;
	for(int i = 0; primes[i] <= sqrt(N); ++i){
		A.push_back(primes[i]*primes[i]);
	}
	for(int i = 0; primes[i] <= cbrt(N); ++i){
		B.push_back(primes[i]*primes[i]*primes[i]);
	}
	for(int i = 0; primes[i] <= sqrt(sqrt(N)); ++i){
		C.push_back(primes[i]*primes[i]*primes[i]*primes[i]);
	}
	vector<int> res(N+1);
	for(int i = 0; i < A.size(); ++i){
		for(int j = 0; j < B.size(); ++j){
			for(int k = 0; k < C.size(); ++k){
				lli r = A[i] + B[j] + C[k];
				if(r <= N){
					res[r]++;
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0; i <= N; ++i){
		if(res[i]) ans++;
	}
	cout << ans << "\n";
	return 0;
}