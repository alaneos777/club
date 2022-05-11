#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
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
				R[i + j + d] += ans[i] * ans[j];
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				R[i + j] += R[i + deg] * P[j];
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		nValue += ans[i] * init[i];
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

int H(int n){
	lli ans = 0;
	for(int a0 = 1; a0 <= n; ++a0){
		for(int a1 = 1; a0+a1 <= n; ++a1){
			for(int a2 = 1; a0+a1+a2 <= n; ++a2){
				for(int a3 = max(1, a0-a2+1); a3 <= a0+a1-1 && a0+a1+a2+a3 <= n; ++a3){
					int a4 = a0 + a1 - a3;
					int a5 = a2 + a3 - a0;
					if(a0+a1+a2+a3+a4+a5 <= n){
						ans += 1;
						if(a0 == a1 && a1 == a2 && a2 == a3 && a3 == a4 && a4 == a5){
							ans += 2;
						}
						if(a0 == a2 && a2 == a4 && a1 == a3 && a3 == a5){
							ans += 2;
						}
						if(a0 == a3 && a1 == a4 && a2 == a5){
							ans += 1;
						}
						if(a1 == a5 && a2 == a4){
							ans += 1;
						}
						if(a0 == a2 && a3 == a5){
							ans += 1;
						}
						if(a0 == a4 && a1 == a3){
							ans += 1;
						}
						if(a0 == a5 && a1 == a4 && a2 == a3){
							ans += 1;
						}
						if(a0 == a1 && a2 == a5 && a3 == a4){
							ans += 1;
						}
						if(a0 == a3 && a1 == a2 && a4 == a5){
							ans += 1;
						}
					}
				}
			}
		}
	}
	//assert(ans%12 == 0);
	return ans/12 % mod;
}

int main(){
	vector<lli> init;
	for(int i = 0; i <= 40; ++i){
		init.push_back(H(i));
	}
	vector<lli> P = BerlekampMassey(init);
	for(lli& x : P){
		if(x > mod/2) x -= mod;
	}
	lli N = 55106;
	cout << rec(P, init, N) << "\n";
	return 0;
}