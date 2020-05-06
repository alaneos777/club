#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

map<tuple<int, array<bool, 16>, int>, int> mem;
int f(int n, int idx, const array<bool, 16> & freq, int prev, int mod){
	if(n == 1) return 1;
	if(idx == n+1){
		return 1;
	}
	auto key = make_tuple(idx, freq, prev);
	if(mem.count(key)) return mem[key];
	vector<int> valid;
	if(idx == 1){
		valid.push_back(1);
	}else if(idx == n){
		valid.push_back(n);
	}else{
		for(int d = 2; d <= n-1; ++d){
			valid.push_back(d);
		}
	}
	int ans = 0;
	for(int d : valid){
		if(freq[d-1]) continue;
		if(prev == 0 || abs(d - prev) <= 3){
			auto next = freq;
			next[d-1] = true;
			ans += f(n, idx+1, next, d, mod);
			if(ans >= mod) ans -= mod;
		}
	}
	return mem[key] = ans;
}

lli rec(vector<lli> P, vector<lli> init, lli n, lli mod){
	for(lli & x : P){
		x %= mod;
		if(x < 0) x += mod;
	}
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

lli inverse(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(r0 == 1);
	if(s0 < 0) s0 += n;
	return s0;
}

vector<lli> BerlekampMassey(const vector<lli> & init, lli mod){
	vector<lli> cur, ls;
	lli ld;
	for(int i = 0, m; i < init.size(); ++i){
		lli eval = 0;
		for(int j = 0; j < cur.size(); ++j)
			eval = (eval + init[i-j-1] * cur[j]) % mod;
		eval -= init[i];
		if(eval < 0) eval += mod;
		if(eval == 0) continue;
		if(cur.empty()){
			cur.resize(i + 1);
			m = i;
			ld = eval;
		}else{
			lli k = eval * inverse(ld, mod) % mod;
			vector<lli> c(i - m - 1);
			c.push_back(k);
			for(int j = 0; j < ls.size(); ++j)
				c.push_back((mod-ls[j]) * k % mod);
			if(c.size() < cur.size()) c.resize(cur.size());
			for(int j = 0; j < cur.size(); ++j){
				c[j] += cur[j];
				if(c[j] >= mod) c[j] -= mod;
			}
			if(i - m + ls.size() >= cur.size())
				ls = cur, m = i, ld = eval;
			cur = c;
		}
	}
	if(cur.empty()) cur.push_back(0);
	reverse(cur.begin(), cur.end());
	return cur;
}

int main(){
	lli mod_f = lli(1e18) + 3;
	lli mod_s = 1e9;

	vector<lli> init_f;
	for(int i = 1; i <= 16; ++i){
		array<bool, 16> freq;
		for(int d = 0; d < 16; ++d) freq[d] = false;
		mem.clear();
		init_f.push_back(f(i, 1, freq, 0, mod_s));
	}

	vector<lli> p_f = BerlekampMassey(init_f, mod_f);
	init_f.resize(p_f.size());
	for(lli & x : p_f){
		if(x > mod_f/2){
			x -= mod_f;
		}
	}

	vector<lli> a_s1;
	lli sum_1 = 0;
	int deg = (p_f.size() + 2) * (p_f.size() + 1) * p_f.size() / 6 + 1;
	for(int i = 1; i <= 2*deg; ++i){
		lli fi = rec(p_f, init_f, i-1, mod_f);
		fi = fi * fi % mod_f * fi % mod_f;
		sum_1 += fi;
		if(sum_1 >= mod_f) sum_1 -= mod_f;
		a_s1.push_back(sum_1);
	}

	vector<lli> p = BerlekampMassey(a_s1, mod_f);
	for(lli & x : p){
		if(x > mod_f/2){
			x -= mod_f;
		}
		x %= mod_s;
		if(x < 0) x += mod_s;
	}

	vector<lli> a_s2;
	lli sum_2 = 0;
	for(int i = 1; i <= p.size(); ++i){
		lli fi = rec(p_f, init_f, i-1, mod_s);
		fi = fi * fi % mod_s * fi % mod_s;
		sum_2 += fi;
		if(sum_2 >= mod_s) sum_2 -= mod_s;
		a_s2.push_back(sum_2);
	}

	cout << (int64_t)rec(p, a_s2, lli(1e14)-1, mod_s) << "\n";
	return 0;
}