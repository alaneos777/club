#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto lpSieve(int n){
	vector<int> primes;
	vector<int> lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			lp[i] = i;
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return lp;
}

const int M = 12345678;
const auto lp = lpSieve(M);

auto factorice(int n){
	vector<pair<int, int>> f;
	while(n > 1){
		int p = lp[n], a = 0;
		while(n%p == 0){
			n /= p;
			a++;
		}
		f.emplace_back(p, a);
	}
	return f;
}

lli g(int n){
	if(n&1) return -n;
	auto fact = factorice(n);
	function<lli(int, int, int)> go = [&](int pos, int phi, int f) -> lli{
		if(pos == fact.size()){
			return phi * lli(n/f);
		}else{
			lli ans = 0;
			auto[p, a] = fact[pos];
			int f_pow = 1, ph = 1;
			for(int i = 0; i <= a; ++i){
				if(p != 2 || i >= 1) ans += go(pos+1, phi*ph, f*f_pow);
				if((i&1) == 0) f_pow *= p;
				if(i == 0) ph = p-1;
				else ph *= p;
			}
			return ans;
		}
	};
	return go(0, 1, 1);
}

lli G(int n){
	lli ans = 0;
	for(int i = 1; i <= n; ++i){
		ans += g(i);
	}
	return ans;
}

int main(){
	cout << G(M) << "\n";
	return 0;
}