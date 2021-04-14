#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto rec(const vector<lli> & P, lli n, int mod){
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
	return ans;
}

auto lpSieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
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

const auto lp = lpSieve(2e6);

void fact(int n, map<int, int>& fact){
	while(n > 1){
		int p = lp[n];
		int a = 0;
		while(n % p == 0){
			n /= p;
			a++;
		}
		fact[p] += a;
	}
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

lli order(int k){
	map<int, int> f, f_order;
	fact(k, f);
	lli order = 1;
	for(auto [p, a] : f){
		f_order[p] += a;
		order *= power(p, a) * (p+1) * (p-1);
		fact(p+1, f_order);
		fact(p-1, f_order);
	}
	if(rec({6, 2}, order, k) != vector<lli>{1, 0}){
		return 0;
	}
	for(auto [p, a] : f_order){
		order /= power(p, a);
		while(rec({6, 2}, order, k) != vector<lli>{1, 0}){
			order *= p;
		}
	}
	return order;
}

int main(){
	int M = 1e6;
	lli ans = 0;
	for(int k = 2; k <= M; ++k){
		if(k%6 == 1 || k%6 == 5) ans += order(k);
	}
	cout << ans << "\n";
	return 0;
}