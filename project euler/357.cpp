#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<bool> isPrime;
void sieve(int n){
	vector<int> primes;
	isPrime.resize(n+1, true);
	isPrime[0] = isPrime[1] = false;
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

const int N = 1e8;

int main(){
	sieve(N+10);
	lli sum = 1;
	for(lli i = 2; i <= N; i += 4){
		if(isPrime[i+1] && isPrime[i/2+2]){
			bool test = true;
			for(lli d = 1; d*d <= i; ++d){
				if(i % d != 0) continue;
				if(!isPrime[d+i/d]){
					test = false;
					break;
				}
			}
			if(test) sum += i;
		}
	}
	cout << sum << "\n";
	return 0;
}