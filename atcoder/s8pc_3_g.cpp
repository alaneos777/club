#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 998244353;

lli inverse(lli a){
	lli r0 = a, r1 = mod, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(r0 == 1);
	if(s0 < 0) s0 += mod;
	return s0;
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

int ncr(lli n, lli r){
	if(r < 0 || r > n) return 0;
	r = min(r, n - r);
	lli ans = 1;
	for(lli den = 1, num = n % mod; den <= r; den++, num--){
		ans = ans * num % mod * inverse(den) % mod;
	}
	return ans;
}

auto mult(const vector<int> & a, const vector<int> & b){
	vector<int> c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			c[i+j] += (lli)a[i] * b[j] % mod;
			if(c[i+j] >= mod) c[i+j] -= mod;
		}
	}
	return c;
}

void clean(vector<int> & poly){
	while(!poly.empty() && poly.back() == 0) poly.pop_back();
	if(poly.empty()) poly.push_back(0);
}

auto quotient(const vector<int> & a, const vector<int> & b){
	vector<int> r = a, ans;
	while(r.size() >= b.size() && !(r.size() == 1 && r[0] == 0)){
		size_t g = r.size() - b.size();
		lli q = r.back() * inverse(b.back()) % mod;
		if(ans.size() <= g) ans.resize(g+1);
		ans[g] += q;
		if(ans[g] >= mod) ans[g] -= mod;
		for(int i = 0; i < b.size(); ++i){
			r[i+g] -= b[i] * q % mod;
			if(r[i+g] < 0) r[i+g] += mod;
		}
		clean(r);
		clean(ans);
	}
	assert(r.size() == 1 && r[0] == 0);
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n; lli m;
	cin >> n >> m;
	--n;
	if(n == 0){
		cout << rec({1, 1}, {0, 1}, m) << "\n";
		return 0;
	}
	vector<int> num(n+1);
	lli curr = 1;
	for(int i = 0; i <= n; ++i){
		num[i] = curr;
		if(!(i & 1)) num[i] = mod - num[i];
		curr = curr * (n - i) % mod * inverse(i + 1) % mod;
	}
	num = mult(num, {(int)rec({1, 1}, {0, 1}, 2*n), (int)rec({1, 1}, {0, 1}, 2*n-1)});
	num[1] = (num[1] + 1) % mod;
	vector<int> den = {1, mod-1, mod-1};
	auto P = quotient(num, den);
	lli ans = (rec({1, 1}, {0, 1}, 2*n) * rec({1, 1}, {1, 1}, m) % mod + rec({1, 1}, {0, 1}, 2*n-1) * rec({1, 1}, {0, 1}, m) % mod) % mod;
	curr = ncr(m + n-1, n-1);
	for(int i = 0; i <= m && i < P.size(); ++i){
		ans += (lli)P[i] * curr % mod;
		if(ans >= mod) ans -= mod;
		if((m - i + n - 1) % mod == 0){
			curr = ncr(m-(i+1) + n-1, n-1);
		}else{
			curr = curr * ((m - i) % mod) % mod * inverse((m - i + n - 1) % mod) % mod;
		}
	}
	cout << ans << "\n";
	return 0;
}