#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> sieve(int n){
	vector<int> lp(n + 1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; ++i) lp[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lp[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lp[j] == j) lp[j] = i;
	return lp;
}

const int M = 1e8;
const auto lp = sieve(M);

map<lli, lli> mult(const map<lli, lli> & a, const map<lli, lli> & b){
	map<lli, lli> c;
	for(const auto & par1 : a){
		for(const auto & par2 : b){
			c[par1.first + par2.first] += par1.second * par2.second;
		}
	}
	return c;
}

lli ncr(lli n, lli r){
	if(r < 0 || r > n) return 0;
	r = min(r, n - r);
	lli ans = 1;
	for(lli den = 1, num = n; den <= r; den++, num--)
		ans = ans * num / den;
	return ans;
}

lli S(int n){
	if(n == 1) return 1;
	map<lli, lli> pol = {{0, 1}};
	int w = 0, deg = 0;
	while(n > 1){
		int pi = lp[n];
		int ai = 0;
		while(n % pi == 0){
			n /= pi;
			ai++;
		}
		w++;
		deg += ai;
		pol = mult(pol, {{0, 1}, {ai+1, -1}});
	}
	int s = deg / 2;
	lli ans = 0;
	for(const auto & par : pol){
		lli t, coef;
		tie(t, coef) = par;
		lli k = s - t;
		if(k < 0) break;
		ans += coef * ncr(k+w-1, w-1);
	}
	return ans;
}

int main(){
	lli ans = 0;
	for(int n = 1; n <= M; ++n){
		ans += S(n);
	}
	cout << ans << "\n";
	return 0;
}