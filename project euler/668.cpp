#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const lli N = 1e10;
const auto primes = sieve(sqrt(N));

lli cnt = 1;

void dfs(int i, int curr, int k, lli acum){
	if(i == k){
		for(int j = curr; j < primes.size(); ++j){
			lli p = primes[j];
			if(acum * p > N) break;
			lli p_pow = p;
			for(int e = 1; ; ++e){
				lli next = acum * p_pow;
				if(next > N) break;
				if(e == 1){
					if(p < acum){
						cnt++;
						//cout << next << "\n";
					}
				}else if(e == 2){
					if(k >= 2){
						cnt++;
						//cout << next << "\n";
					}
				}else{
					cnt++;
					//cout << next << "\n";
				}
				p_pow *= p;
			}
		}
	}else{
		for(int j = curr; j < primes.size(); ++j){
			lli p = primes[j];
			if(acum * p > N) break;
			lli p_pow = p;
			for(int e = 1; ; ++e){
				lli next = acum * p_pow;
				if(next > N) break;
				dfs(i+1, j+1, k, next);
				p_pow *= p;
			}
		}
	}
}

int main(){
	for(int k = 1; k <= 10; ++k){
		dfs(1, 0, k, 1);
	}
	cout << cnt << "\n";
	return 0;
}