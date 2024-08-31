#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;
const lli mod = 1405695061;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

const int M = 100;
vector<lli> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1), bernoulli(M+1, 1);

lli ncr(lli n, lli r){
	return fact[n] * invfact[r] % mod * invfact[n - r] % mod;
}

using poly = vector<lli>;

poly operator*(const poly& a, const poly& b){
	if(a.empty() || b.empty()) return {};
	poly c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			c[i+j] += a[i]*b[j];
		}
	}
	return c;
}

poly operator-(poly a, const poly& b){
	a.resize(max(a.size(), b.size()));
	for(int i = 0; i < b.size(); ++i){
		a[i] -= b[i];
	}
	return a;
}

lli eval(const poly& a, lli x){
	lli ans = 0;
	for(int i = (int)a.size()-1; i >= 0; --i){
		ans = ans * x + a[i];
	}
	return ans;
}

ld logeval(const poly& a, lli x){
	int r = a.size()-1;
	ld ans = 0;
	for(int i = 1; i <= r; ++i){
		ans += a[r-i] * powl(x, -i) / a[r];
	}
	ans = r * logl(x) + logl(a[r]) + log1pl(ans);
	return ans;
}

lli sum_p(lli n, int m){
	n %= mod;
	lli ans = 0;
	for(int k = 0; k <= m; ++k){
		ans += ncr(m + 1, k) * bernoulli[k] % mod * power(n, m + 1 - k) % mod;
		if(ans >= mod) ans -= mod;
	}
	ans = ans * inv[m + 1] % mod;
	return ans;
}

lli sum(const poly& a, lli L, lli R, lli N){
	if(L > R || a.empty()) return 0;
	lli lo = L, hi = R, lim = -1;
	while(lo <= hi){
		lli mid = (lo + hi) / 2;
		ld logterm = logeval(a, mid);
		lli term = eval(a, mid);
		if(logterm <= logl(N) && term <= N){
			lim = mid;
			lo = mid+1;
		}else{
			hi = mid-1;
		}
	}
	if(lim == -1) return 0;
	lli ans = 0;
	for(int i = 0; i < a.size(); ++i){
		ans += (a[i] % mod) * (sum_p(lim, i) - sum_p(L-1, i)) % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	return ans;
}

lli S(lli K, lli N){
	function<lli(const vector<poly>&, lli)> go = [&](const vector<poly>& u, lli ones) -> lli{
		lli ans = 0;
		if(!u.empty()){
			lli s = sum(u.back(), max(3, (int)u.size()), K, N);
			if(s == 0) return 0;
			ans = s;
		}else{
			ans = sum({1}, max(3, (int)u.size()), K, N);
		}
		for(int i = (int)u.size()-2; i >= 0; --i){
			poly prod = {1};
			for(int j = 0; j < u.size(); ++j){
				if(i == j) continue;
				prod = prod * u[j];
			}
			poly New = prod * poly{0, 1} - u[i];
			auto v = u;
			v.erase(v.begin() + i);
			v.push_back(New);
			(ans += go(v, ones)) %= mod;
		}
		if(ones){
			poly prod = {1};
			for(int j = 0; j < u.size(); ++j){
				prod = prod * u[j];
			}
			poly New = prod * poly{0, 1} - poly{1};
			auto v = u;
			v.push_back(New);
			(ans += go(v, ones - 1)) %= mod;
		}
		return ans;
	};
	return go({}, K);
}

int main(){
	for(int i = 2; i <= M; ++i){
		fact[i] = fact[i-1] * i % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = invfact[i-1] * inv[i] % mod;
	}
	for(int n = 1; n <= M; ++n){
		for(int k = 0; k < n; ++k){
			bernoulli[n] -= bernoulli[k] * ncr(n, k) % mod * inv[n - k + 1] % mod;
			if(bernoulli[n] < 0) bernoulli[n] += mod;
		}
	}
	cout << S(1e18, 1e18) << "\n";
	return 0;
}