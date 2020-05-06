#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e16;

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

const int M = 1e8;
const lli k = 2;
const auto lp = sieve(1.5e6);

void fact(int n, map<int, int> & f){
	while(n > 1){
		int p = lp[n];
		int e = 0;
		while(n % p == 0){
			n /= p;
			e++;
		}
		f[p] += e;
	}
}

inline void modula(lli & n, lli mod){
	while(n >= mod) n -= mod;
}

lli fibo(lli n, lli mod){
	array<lli, 2> F = {1, 0};
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	array<lli, 4> C;
	do{
		int d = (n & p) != 0;
		C[0] = C[3] = 0;
		C[d] = (__int128_t)F[0] * F[0] % mod;
		C[d+1] = (((__int128_t)F[0]) * F[1] << 1) % mod;
		C[d+2] = (__int128_t)F[1] * F[1] % mod;
		F[0] = C[0] + C[2] + C[3];
		F[1] = C[1] + C[2] + (C[3] << 1);
		modula(F[0], mod), modula(F[1], mod);
	}while(p >>= 1);
	return F[1];
}

lli getRank(lli n){
	if(n == 2) return 3;
	if(n == 5) return 5;
	lli order = 1;
	map<int, int> f;
	if(n%10 == 1 || n%10 == 9){
		order = n - 1;
		fact(n - 1, f);
	}else{
		order = n + 1;
		fact(n + 1, f);
	}
	for(const auto & par : f){
		lli p; int e;
		tie(p, e) = par;
		while(e--) order /= p;
		lli state = fibo(order, n);
		while(state != 0){
			order *= p;
			state = fibo(order, n);
		}
	}
	return order;
}

const long double phi = (1 + sqrtl(5)) / 2;

int main(){
	vector<bool> is(k*M+1, true);
	for(int p = 2; p < lp.size()-1; ++p){
		if(lp[p] != p) continue;
		lli rank = getRank(p);
		for(rank *= p; rank <= k*M; rank *= p){
			for(lli i = 0; i <= k*M; i += rank){
				is[i] = false;
			}
		}
	}
	int cnt = 1;
	for(int i = 2; i <= k*M; ++i){
		if(is[i]){
			cnt++;
			if(cnt == M){
				long double lg = i*log10l(phi)-log10l(sqrtl(5));
				int expo = (int)floor(lg);
				long double base = powl(10, lg - expo);
				cout << fixed << setprecision(1) << fibo(i, mod) << "," << base << "e" << expo << "\n";
				break;
			}
		}
	}
	return 0;
}