#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e8;

lli rec(const vector<lli> & P, const vector<lli> & init, lli n){
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

const lli m = 987654321;

int main(){
	lli ans = 0;
	for(int i = 1; i <= 30; ++i){
		ans += rec({-i + mod, 0, (1<<i) % mod}, {3, (1<<i) % mod, (1ll<<(2*i)) % mod}, m) - 1;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	cout << ans << "\n";
	return 0;
}