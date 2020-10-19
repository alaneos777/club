#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const lli mod = 1e9 + 7;

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

auto mult(const vector<lli> & a, const vector<lli> & b){
	vector<lli> c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			(c[i+j] += a[i]*b[j]) %= mod;
		}
	}
	return c;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int d; lli k;
	cin >> d >> k;
	vector<lli> init(d);
	for(lli & di : init){
		cin >> di;
	}
	vector<lli> c(d);
	for(lli & pi : c){
		cin >> pi;
	}
	auto poly = c;
	for(lli & pi : poly){
		pi = (mod - pi) % mod;
	}
	reverse(poly.begin(), poly.end());
	poly.push_back(1);
	poly = mult(poly, {-1+mod, 3, -3+mod, 1});
	poly.pop_back();
	for(lli & pi : poly){
		pi = (mod - pi) % mod;
	}
	lli p, q, r;
	cin >> p >> q >> r;
	for(int n = d; n <= d+2; ++n){
		lli an = 0;
		for(int i = 1; i <= d; ++i){
			(an += c[i-1] * init[n-i]) %= mod;
		}
		(an += p + q*n%mod + r*n%mod*n%mod) %= mod;
		init.push_back(an);
	}
	cout << rec(poly, init, k) << "\n";
	return 0;
}