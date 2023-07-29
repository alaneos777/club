#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 999676999;

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

auto lpSieve(int n){
	vector<int> lp(n+1), primes;
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

const int M = 5e4;
const auto lp = lpSieve(M);

int D(int n){
	if(n == 1) return 1;
	int ans = 0, tmp = n;
	while(tmp > 1){
		int p = lp[tmp], a = 0;
		while(tmp % p == 0){
			tmp /= p;
			a++;
		}
		ans += n/p*a;
	}
	return ans;
}

vector<int> invert(const vector<int>& P){
	vector<int> Q(P.size());
	lli inv0 = powerMod(P[0], mod-2);
	Q[0] = inv0;
	for(int i = 1; i < Q.size(); ++i){
		for(int j = 0; j < i; ++j){
			Q[i] -= (lli)Q[j]*P[i-j] % mod;
			if(Q[i] < 0) Q[i] += mod;
		}
		Q[i] = Q[i] * inv0 % mod;
	}
	return Q;
}

int G(int N){
	vector<int> P = {1};
	for(int i = 1; i <= N; ++i){
		int Di = D(i);
		vector<int> Q = P;
		for(int j = 0; j < P.size() && j+i <= N; ++j){
			if(j+i >= Q.size()) Q.resize(j+i+1);
			Q[j+i] -= (lli)Di * P[j] % mod;
			if(Q[j+i] < 0) Q[j+i] += mod;
		}
		P = Q;
	}
	P = invert(P);
	int ans = 0;
	for(int i = 1; i <= N; ++i){
		ans += P[i];
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int main(){
	cout << G(M) << "\n";
	return 0;
}