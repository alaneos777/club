#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int8_t> Mu(1e6 + 1);
bitset<1000001> isPrime;
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

lli S(lli n){
	lli ans = 0;
	for(lli k = 1; k*k <= n; ++k)
		ans += Mu[k] * (n / (k * k));
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	muSieve(1e6);
	int t;
	cin >> t;
	while(t--){
		lli n;
		cin >> n;
		lli l = 1, r = 1e12;
		while(l < r){
			lli m = (l + r) / 2;
			lli cnt = S(m);
			if(cnt < n) l = m + 1;
			else r = m;
		}
		cout << l << "\n";
	}
	return 0;
}