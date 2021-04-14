#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	while(e){
		if(e & 1) ans = ans * b % m;
		e >>= 1;
		b = b * b % m;
	}
	return ans;
}

vector<int> primes;
auto lp_sieve(int n){
	vector<int> lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return lp;
}

const auto lp = lp_sieve(6e6);

auto fact(int n){
	vector<int> pr;
	while(n > 1){
		int p = lp[n];
		while(n % p == 0) n /= p;
		pr.push_back(p);
	}
	return pr;
}

int generator(int p){
	auto f = fact(p-1);
	for(int g = 2; g < p; ++g){
		bool test = true;
		for(int pr : f){
			if(powerMod(g, (p-1) / pr, p) == 1){
				test = false;
				break;
			}
		}
		if(test) return g;
	}
	assert(0);
	return -1;
}

int main(){
	uint64_t ans = 0;
	for(int p : primes){
		if(p == 3){
			lli sols = 2;
			ans += sols;
		}else if(p % 3 == 2){
			lli sols = lli(p-1)*(p-2);
			ans += sols;
		}else{
			lli g = generator(p);
			lli g3 = g*g % p * g % p;
			vector<bool> F(p);
			int len = (p-1) / 3;
			int g_pow = 1;
			F[g_pow] = 1;
			for(int i = 1; i < len; ++i){
				g_pow = g_pow * g3 % p;
				F[g_pow] = 1;
			}
			lli sols = 0;
			for(int r = 0, s = 1; r < p; ++r, ++s){
				if(s == p) s == 0;
				if(F[r] && F[s]) sols++;
			}
			sols *= 9*(p-1);
			ans += sols;
			//cout << p << " " << sols << " " << ans << "\n";
		}
	}
	cout << ans << "\n";
	return 0;
}