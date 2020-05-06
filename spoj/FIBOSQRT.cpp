#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli a, b, m, n;
		cin >> a >> b >> m >> n;
		lli c = a + b + 2*lli(round(sqrtl(3 + a*b)));
		a %= m, b %= m, c %= m;
		cout << rec({-1+m, 2%m, 2%m}, {a, b, c}, n, m) << "\n";
	}
	return 0;
}