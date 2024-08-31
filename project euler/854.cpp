#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1234567891;

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

vector<lli> BerlekampMassey(const vector<lli> & init){
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
	int MX = 40, L = 1e6;
	vector<lli> F(MX+1);
	F[0] = 0, F[1] = 1;
	for(int i = 2; i <= MX; ++i){
		F[i] = F[i-1] + F[i-2];
	}
	vector<lli> init(MX);
	for(int i = 1; i < MX; ++i){
		init[i] = __gcd(F[i], abs(F[i-1]-1)) % mod;
	}
	auto P = BerlekampMassey(init);
	init.resize(L+1);
	for(int i = MX; i <= L; ++i){
		for(int j = 1; j <= P.size(); ++j){
			(init[i] += P[P.size() - j] * init[i-j]) %= mod;
		}
	}
	lli prod = 2;
	for(int n = 6; n <= L; n += 2){
		prod = prod * init[n] % mod;
	}
	cout << prod << "\n";
	return 0;
}