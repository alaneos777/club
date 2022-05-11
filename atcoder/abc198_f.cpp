#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;

lli power(lli a, lli b){
	a %= mod;
	b %= mod-1;
	if(b < 0) b += mod-1;
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli ncr(lli n, lli r){
	if(r < 0 || r > n) return 0;
	r = min(r, n-r);
	lli ans = 1;
	for(lli num = n, den = 1; den <= r; --num, ++den){
		ans = ans * (num % mod) % mod * power(den % mod, -1) % mod;
	}
	return ans;
}

lli a(int l, int r, lli n){
	if(n%l != 0) return 0;
	return ncr(n/l - 1, r - 1);
}

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

lli b(lli n){
	if(n < 6) return 0;
	return rec({1, -2+mod, 1, 0, -1+mod, 2}, {1, 2, 3, 4, 6, 8}, n-6);
}

lli c(lli n){
	if(n < 6) return 0;
	return rec({-1+mod, 2, 1, -4+mod, 1, 2}, {1, 2, 5, 8, 14, 20}, n-6);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli s;
	cin >> s;
	lli ans = (a(1,6,s) + 6*b(s)%mod + 3*c(s)%mod + 8*a(3,2,s)%mod + 6*a(2,3,s)%mod) % mod;
	ans = ans * power(24, -1) % mod;
	cout << ans << "\n";
	return 0;
}