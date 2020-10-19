#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

auto sieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0) primes.push_back(i), lp[i] = i;
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			lp[d] = p;
			if(p == lp[i]) break;
		}
	}
	return lp;
}

lli r2(lli n, const map<lli, int> & fact){
	if(n == 0) return 1;
	lli ans = 4;
	for(const auto & par : fact){
		lli p; int e;
		tie(p, e) = par;
		if(p == 2){
			ans *= 1;
		}else if(p % 4 == 3){
			if(e % 2 == 0){
				ans *= 1;
			}else{
				ans = 0;
			}
		}else{
			ans *= e + 1;
		}
	}
	return ans;
}

const lli N = 9765625; //5^10

const auto lp = sieve(2*N);

void factorice(int n, map<lli, int> & fact){
	while(n > 1){
		int p = lp[n];
		int e = 0;
		while(n % p == 0){
			n /= p;
			e++;
		}
		fact[p] += e;
	}
}

int main(){
	srand(time(0));
	lli ans = 0;
	for(lli x = 0; x <= N; ++x){
		map<lli, int> fact;
		factorice(N + x, fact);
		factorice(N - x, fact);
		ans += x * r2(N*N - x*x, fact);
	}
	cout << ans * 1024 * 6 << endl;
	return 0;
}