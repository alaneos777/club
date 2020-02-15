#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> sieve(int n){
	vector<int> primes;
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const vector<int> primes = sieve(1000000);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	set<lli> ans;
	for(lli p : primes){
		ans.insert(p*p);
	}
	int t;
	cin >> t;
	while(t--){
		lli n;
		cin >> n;
		if(ans.count(n)){
			cout << "YES\n";
		}else{
			cout << "NO\n";
		}
	}
	return 0;
}