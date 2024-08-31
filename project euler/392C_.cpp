#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

lli power(lli a, lli b){
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

const int M = 100;
vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);

using poly = vector<int>;

poly operator*(poly a, lli b){
    for(int& x : a){
        x = x * b % mod;
    }
    return a;
}

poly operator-(poly a, const poly& b){
    a.resize(max(a.size(), b.size()));
    for(int i = 0; i < b.size(); ++i){
        a[i] -= b[i];
        if(a[i] < 0) a[i] += mod;
    }
    return a;
}

poly operator/(const poly& a, const poly& b){
    assert(a.size() == b.size());
    int n = a.size();
    poly c(n);
    lli inv_b0 = power(b[0], mod-2);
    c[0] = a[0] * inv_b0 % mod;
    for(int i = 1; i < n; ++i){
        c[i] = a[i];
        for(int j = 1; j <= i; ++j){
            c[i] -= (lli)b[j] * c[i-j] % mod;
            if(c[i] < 0) c[i] += mod;
        }
        c[i] = c[i] * inv_b0 % mod;
    }
    return c;
}

poly Exp(lli n, int sz){
    n %= mod;
    poly a(sz);
    lli n_pow = 1;
    for(int i = 0; i < sz; ++i){
        a[i] = n_pow * invfact[i] % mod;
        n_pow = n_pow * n % mod;
    }
    return a;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for(lli i = 2; i <= M; ++i){
        fact[i] = fact[i-1] * i % mod;
        inv[i] = mod - inv[mod % i] * (mod / i) % mod;
        invfact[i] = (lli)invfact[i-1] * inv[i] % mod;
    }
    lli n; int k;
    cin >> n >> k;
    poly numerator = poly{1} - Exp(n+2, k+1) * rec({1, 1}, {0, 1}, n+1) - Exp(n+1, k+1) * rec({1, 1}, {0, 1}, n+2);
    poly denominator = poly{1} - Exp(1, k+1) - Exp(2, k+1);
    lli ans = (numerator / denominator)[k] * (lli)fact[k] % mod;
    cout << ans << "\n";
    return 0;
}