#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9;

int K;

using poly = vector<int>;
poly operator*(const poly& a, const poly& b){
	if(a.size() == 0 || b.size() == 0) return {};
	poly c(min(K, int(a.size() + b.size() - 1)));
	for(int i = 0; i < a.size() && i < K; ++i){
		for(int j = 0; j < b.size() && i+j < K; ++j){
			c[i+j] += (lli)a[i]*b[j] % mod;
			if(c[i+j] >= mod) c[i+j] -= mod;
		}
	}
	return c;
}

poly operator+(const poly& a, const poly& b){
	poly c(max(a.size(), b.size()));
	for(int i = 0; i < a.size(); ++i){
		c[i] += a[i];
		if(c[i] >= mod) c[i] -= mod;
	}
	for(int i = 0; i < b.size(); ++i){
		c[i] += b[i];
		if(c[i] >= mod) c[i] -= mod;
	}
	if(c.size() > K) c.resize(K);
	return c;
}

poly solveRecurrence(const vector<poly> & P, const vector<poly> & init, lli n){
	int deg = P.size();
	vector<poly> ans(deg), R(2*deg);
	ans[0] = {1};
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), poly{});
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				R[i + j + d] = R[i+j+d] + ans[i] * ans[j];
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				R[i + j] = R[i+j] + R[i + deg] * P[j];
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	poly nValue = {};
	for(int i = 0; i < deg; i++)
		nValue = nValue + ans[i] * init[i];
	return nValue;
}

int main(){
	int n, m, k;
	cin >> n >> m >> k;
	int deg = 0;
	vector<int> d(m), p(m);
	for(int i = 0; i < m; ++i){
		cin >> d[i] >> p[i];
		deg = max(deg, d[i]);
	}
	K = k+1;
	vector<poly> coef(deg+1, poly(k+1));
	for(int i = 0; i < m; ++i){
		coef[d[i]][p[i]]++;
		if(coef[d[i]][p[i]] >= mod) coef[d[i]][p[i]] -= mod;
	}
	vector<poly> init(deg), P(deg);
	init[0] = {1};
	for(int i = 1; i < deg; ++i){
		for(int j = 0; j <= i; ++j){
			init[i] = init[i] + coef[j] * init[i-j];
		}
	}
	reverse(coef.begin(), coef.end());
	coef.pop_back();
	poly res = solveRecurrence(coef, init, n-1);
	lli ans = 0;
	for(int i = 0; i < res.size() && i <= k; ++i){
		ans += res[i];
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}