#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;

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

const int M = 3000;

vector<lli> operator*(const vector<lli>& a, const vector<lli>& b){
	vector<lli> c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			(c[i+j] += (lli)a[i]*b[j]) %= mod;
		}
	}
	return c;
}

vector<lli> div(const vector<lli>& a, const vector<lli>& b, int sz){
	vector<lli> c(sz);
	for(int i = 0; i < b.size() && i < sz; ++i){
		c[i] = i < a.size() ? a[i] : 0;
		for(int j = 0; j < i; ++j){
			c[i] -= c[j]*b[i-j]%mod;
			if(c[i] < 0) c[i] += mod;
		}
	}
	return c;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
	vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);
	for(lli i = 2; i <= M; ++i){
		fact[i] = i*fact[i-1] % mod;
		inv[i] = mod - (mod/i)*inv[mod%i] % mod;
		invfact[i] = (lli)inv[i]*invfact[i-1] % mod;
	}
	auto ncr = [&](int n, int r) -> lli{
		if(r < 0 || r > n) return 0;
		return (lli)fact[n] * invfact[r] % mod * invfact[n-r] % mod;
	};

	int t;
	cin >> t;
	while(t--){
		lli n; int k;
		cin >> n >> k;
		vector<lli> P = {1, 0, -1+mod, 0, -2+mod, 0, -3+mod, 0, 1};
		vector<lli> Q(k+1);
		for(int i = 0; i <= k; ++i){
			Q[i] = ncr(k, i);
			if((i&1) == 1) Q[i] = (mod - Q[i]) % mod;
		}
		vector<lli> den = P*Q;
		vector<lli> num = {1, 2, 1, 1, 2, 3, -1+mod, -1+mod};
		vector<lli> init = div(num, den, k+8);
		reverse(den.begin(), den.end());
		assert(den.back()==1);
		den.pop_back();
		for(lli& x : den){
			x = (mod-x) % mod;
		}
		cout << rec(den, init, n-1) << "\n";
	}
	return 0;
}