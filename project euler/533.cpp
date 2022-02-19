#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int lcm(int a, int b){
	return a / __gcd(a, b) * b;
}

int car(int p, int e, int pe){
	if(e <= 2 || p >= 3) return pe/p * (p-1);
	else return pe/p * (p-1) / 2;
}

auto phiSieve(int n){
	vector<int> primes, lp(n+1), cnt(n+1), lp_pow(n+1), phi(n+1, 1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
			phi[i] = car(i, 1, i);
			cnt[i] = 1;
			lp_pow[i] = i;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p){
				phi[d] = lcm(phi[i / lp_pow[i]], car(p, cnt[i] + 1, lp_pow[i]*p));
				cnt[d] = cnt[i] + 1;
				lp_pow[d] = lp_pow[i] * p;
				break;
			}else{
				phi[d] = lcm(phi[i], car(p, 1, p));
				cnt[d] = 1;
				lp_pow[d] = p;
			}
		}
	}
	return phi;
}

int main(){
	int N = 1e7;
	vector<int> phi = phiSieve(N), ans(N+1);
	for(int i = 1; i <= N; ++i){
		ans[phi[i]] = i;
	}
	for(int i = 2; i <= 100; i += 2){
		cout << i << " " << ans[i] << "\n";
	}
	return 0;
}

/*
http://oeis.org/search?q=24%2C240%2C504%2C480%2C264%2C65520&sort=&language=&go=Search
http://oeis.org/A002174
*/