#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

vector<int> primes;
vector<bool> isPrime;

void sieve(int n){
	isPrime.resize(n+1, true);
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
}

const int M = 1e8;

int main(){
	sieve(M);
	vector<int> pi(M+1);
	for(int i = 1; i <= M; ++i){
		pi[i] = pi[i-1] + isPrime[i];
	}
	vector<int> values(M+1);

	lli ans = 1;
	for(int i = 2; i <= M; ++i){
		int u = pi[i];
		int cnt = !isPrime[i];
		while(u){
			if(!isPrime[u]){
				cnt++;
			}
			values[cnt]++;
			u = pi[u];
		}
	}
	for(int i = 0; i <= M; ++i){
		if(values[i]) ans = ans * values[i] % mod;
	}

	cout << ans << "\n";
	return 0;
}