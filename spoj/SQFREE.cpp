#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> Mu(1e7 + 1);
bitset<10000001> isPrime;
vector<int> primes;

void muSieve(int n){
	Mu[0] = 0, Mu[1] = 1;
	isPrime.set();
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){
			primes.push_back(i);
			Mu[i] = -1;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0){
				break;
			}else{
				Mu[d] = -Mu[i];
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	muSieve(1e7);
	int t;
	cin >> t;
	while(t--){
		lli n, ans = 0;
		cin >> n;
		for(lli k = 1; k*k <= n; ++k){
			ans += Mu[k] * (n / (k * k));
		}
		cout << ans << "\n";
	}
	return 0;
}