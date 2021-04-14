#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

vector<int> lp, mu;
void sieve(int n){
	vector<int> primes;
	lp.resize(n+1), mu.resize(n+1);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
			else{
				mu[d] = -mu[i];
			}
		}
	}
}

vector<int> divs(int n){
	vector<int> pr;
	while(n > 1){
		int p = lp[n];
		while(n % p == 0){
			n /= p;
		}
		pr.push_back(p);
	}
	vector<int> divs;
	function<void(int, int)> go = [&](int pos, int acum){
		if(pos == pr.size()){
			divs.push_back(acum);
		}else{
			go(pos+1, acum);
			go(pos+1, acum * pr[pos]);
		}
	};
	go(0, 1);
	return divs;
}

lli f(int c, int n){
	lli ans = 0;
	for(int d : divs(c)){
		ans += mu[d] * (n/d - c/d);
	}
	return ans;
}

const int N = 1e8;

int main(){
	sieve(N);
	lli ans = 1;
	for(int c = 2; c <= N; ++c){
		//if(c % 100000 == 0) cout << c << "\n";
		ans = ans * power(c, f(c, N)) % mod;
	}
	cout << ans << "\n";
	return 0;
}