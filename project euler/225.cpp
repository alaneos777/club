#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> sieve(int n){
	vector<int> lp(n+1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; ++i) lp[i] = (i&1 ? i : 2);
	for(int i = 3; i*i <= n; i += 2){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += 2*i){
				if(lp[j] == j) lp[j] = i;
			}
		}
	}
	return lp;
}

const int M = 1e6;
const auto lp = sieve(M);

void fact(lli n, map<lli, int> & f){
	if(n <= M){
		while(n > 1){
			int p = lp[n], e = 0;
			while(n % p == 0){
				n /= p;
				e++;
			}
			f[p] += e;
		}
	}else{
		for(lli p = 2; p*p <= n; ++p){
			int e = 0;
			while(n % p == 0){
				n /= p;
				e++;
			}
			if(e) f[p] += e;
		}
		if(n > 1) f[n]++;
	}
}

lli rec(const vector<lli> & P, const vector<lli> & init, lli n, lli mod){
	int deg = P.size();
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				(R[i + j + d] += ans[i] * ans[j]) %= mod;
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				(R[i + j] += R[i + deg] * P[j]) %= mod;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		(nValue += ans[i] * init[i]) %= mod;
	return nValue;
}

array<lli, 3> tribo(lli n, lli mod){
	return {rec({1, 1, 1}, {1, 1, 1}, n, mod), rec({1, 1, 1}, {1, 1, 1}, n+1, mod), rec({1, 1, 1}, {1, 1, 1}, n+2, mod)};
}

lli period_prime(int p, int e){
	map<lli, int> f;
	f[p] = e;
	fact(p-1, f);
	fact(p+1, f);
	fact(p*p + p + 1, f);
	lli mod = 1;
	for(int i = 1; i <= e; ++i) mod *= p;
	__int128_t period = mod * lli(p-1) * lli(p+1) * (lli(p)*p + p + 1);
	for(const auto & par : f){
		lli pr; int er;
		tie(pr, er) = par;
		while(er--) period /= pr;
		auto state = tribo(period, mod);
		while(!(state[0] == 1 && state[1] == 1 && state[2] == 1)){
			period *= pr;
			state = tribo(period, mod);
		}
	}
	return period;
}

lli lcm(lli a, lli b){
	return a / __gcd(a, b) * b;
}

lli period(lli n){
	map<lli, int> f;
	fact(n, f);
	lli period = 1;
	for(const auto & par : f){
		period = lcm(period, period_prime(par.first, par.second));
	}
	return period;
}

bool zero(lli n){
	lli p = period(n);
	for(lli i = 0; i < p; ++i){
		if(rec({1, 1, 1}, {1, 1, 1}, i, n) == 0){
			return false;
		}
	}
	return true;
}

int main(){
	int cnt = 0;
	for(int d = 3; ; d += 2){
		if(zero(d)){
			cnt++;
			if(cnt == 124){
				cout << d << "\n";
				break;
			}
		}
	}
	return 0;
}