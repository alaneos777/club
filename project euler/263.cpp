#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> primes, lp;
vector<bool> isPrime;
void sieve(int n){
	lp.resize(n+1);
	isPrime.resize(n+1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){
			primes.push_back(i);
			lp[i] = i;
		}
		for(int p : primes){
			int d = i*p;
			if((lli)i*p > n) break;
			isPrime[d] = false;
			lp[d] = p;
			if(i % p == 0) break;
		}
	}
}

const int M = 1.2e9;

bool isPractical(int n){
	if(n & 1) return false;
	vector<pair<int, int>> fact;
	while(n > 1){
		int p = lp[n], p_pow = 1;
		while(n % p == 0){
			n /= p;
			p_pow *= p;
		}
		fact.emplace_back(p, p_pow);
	}
	lli prod = 1;
	for(int i = 0; i < fact.size(); ++i){
		lli p, p_pow;
		tie(p, p_pow) = fact[i];
		if(p > prod+1) return false;
		prod = prod * ((p_pow*p - 1) / (p - 1));
	}
	return true;
}

int main(){
	sieve(M+10);
	int cnt = 0;
	lli sum = 0;
	for(int m = 1; 840*m <= M; ++m){
		for(int n : {840*m + 20, 840*m + 820}){
			bool cond = true;
			for(int i = -9; i <= 9; ++i){
				if(i%3 == 0 && i%2 != 0){
					cond &= isPrime[n+i];
				}else{
					cond &= !isPrime[n+i];
				}
			}
			if(cond && isPractical(n-8) && isPractical(n-4) && isPractical(n) && isPractical(n+4) && isPractical(n+8)){
				cout << n << " ";
				sum += n;
				cnt++;
				if(cnt == 4){
					break;
				}
			}
		}
	}
	cout << "\n" << sum << "\n";
	return 0;
}