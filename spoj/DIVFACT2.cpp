#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<int> primes;
vector<bool> isPrime;
void sieve(int n){
	isPrime.assign(n+1, true);
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

int main(){
	//ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	sieve(1e8);
	cout << primes.size();
	int t;
	lli n, m;
	cin >> t;
	while(t--){
		cin >> n >> m;
	}
	return 0;
}