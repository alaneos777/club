#include <bits/stdc++.h>
using namespace std;

vector<int8_t> muSieve(int n){
	vector<int8_t> mu(n+1);
	mu[0] = 0, mu[1] = 1;
	vector<int> primes;
	vector<bool> isPrime(n+1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){
			primes.push_back(i);
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0){
				break;
			}else{
				mu[d] = -mu[i];
			}
		}
	}
	return mu;
}

const int N = 1e9;
const int lim = 1e6;

const auto mu = muSieve(lim);

vector<int> mertens_small(lim+1), sqfree_small(lim+1);
map<int, int> mertens_big;

int mertens(int n){
	if(n <= lim) return mertens_small[n];
	if(mertens_big.count(n)) return mertens_big[n];
	int m = sqrt(n), l = n / m;
	int ans = 1;
	for(int i = 2; i <= l; ++i){
		ans -= mertens(n / i);
	}
	for(int i = 1; i < m; ++i){
		ans -= (n / i - n / (i + 1)) * mertens(i);
	}
	return mertens_big[n] = ans;
}

int sqfree(int n){
	if(n <= lim) return sqfree_small[n];
	int m = sqrt(n);
	int ans = 0;
	for(int i = 1; i <= m; ++i){
		ans += mu[i] * (n / (i * i));
	}
	return ans;
}

int main(){
	for(int i = 1; i <= lim; ++i){
		mertens_small[i] = mertens_small[i-1] + mu[i];
		sqfree_small[i] = sqfree_small[i-1] + abs(mu[i]);
	}
	int ans = 0;
	for(int i = 1; i <= lim; ++i){
		ans += mertens(N/powl(i, 1.5l)) + sqfree(N/powl(i, 1.5l));
	}
	ans /= 2;
	cout << ans << "\n";
	return 0;
}