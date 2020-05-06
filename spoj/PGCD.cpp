#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 1e7 + 100;
bitset<M+100> isPrime;
vector<int> primes;

auto muSieve(int n){
	vector<int> Mu(n+1);
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
	return Mu;
}

const auto mu = muSieve(M);
vector<lli> mertens(M+1);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int i = 1; i <= M; ++i){
		mertens[i] = mertens[i-1] + mu[i];
	}
	int t;
	cin >> t;
	while(t--){
		int m, n;
		cin >> m >> n;
		lli ans = 0;
		for(int p : primes){
			int a = m / p, b = n / p;
			int limit = min(a, b);
			if(limit == 0) break;
			int d = 1;
			while(d <= limit){
				int ad = a / d, bd = b / d;
				int u = min(a / ad, b / bd);
				ans += (mertens[u] - mertens[d-1]) * ad * bd;
				d = u + 1;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}