#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1234567891;
const long double a = 3 + 2*sqrtl(2);

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli rec(const vector<lli>& P, const vector<lli>& init, lli n){
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

int main(){
	lli r = 1e10;
	lli M = powerMod(10, r/2) * powerMod(2, mod-2) % mod;
	lli S1 = M * (M+1) % mod * (4*M-1) % mod * powerMod(3, mod-2) % mod - 2;
	if(S1 < 0) S1 += mod;
	lli K = (lli)floorl((logl(2*sqrtl(2)) + r*logl(10))/logl(a));
	lli S2 = rec({-1+mod, 6}, {powerMod(2, mod-2), 5*powerMod(2, mod-2) % mod}, K) - 5*powerMod(2, mod-2)%mod;
	if(S2 < 0) S2 += mod;
	lli S = (S1 + S2 - 12) % mod;
	if(S < 0) S += mod;
	cout << S << "\n";
	return 0;
}