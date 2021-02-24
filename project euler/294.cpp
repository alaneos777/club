#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli modulo = 1e9 + 7;
const lli mod = 1e9;

const int M = 1000;
int ten[M+1];
int mem[M+1][24][23];

int f(int n, int m, int pos = 0, int sum = 0, int rem = 0){
	if(pos == n) return rem == 0 && sum == 23;
	int& ans = mem[pos][sum][rem];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 9; ++d){
		if(sum + d > 23) break;
		ans += f(n, m, pos+1, sum + d, (rem + d*ten[pos]) % 23);
		if(ans >= m) ans -= m;
	}
	return ans;
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
			eval = (eval + init[i-j-1] * cur[j]) % modulo;
		eval -= init[i];
		if(eval < 0) eval += modulo;
		if(eval == 0) continue;
		if(cur.empty()){
			cur.resize(i + 1);
			m = i;
			ld = eval;
		}else{
			lli k = eval * inverse(ld, modulo) % modulo;
			vector<lli> c(i - m - 1);
			c.push_back(k);
			for(int j = 0; j < ls.size(); ++j)
				c.push_back((modulo-ls[j]) * k % modulo);
			if(c.size() < cur.size()) c.resize(cur.size());
			for(int j = 0; j < cur.size(); ++j){
				c[j] += cur[j];
				if(c[j] >= modulo) c[j] -= modulo;
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
	ten[0] = 1;
	for(int i = 1; i <= M; ++i){
		ten[i] = 10ll * ten[i-1] % 23;
	}
	vector<lli> initial, init;
	for(int i = 0; i <= M; ++i){
		memset(mem, -1, sizeof(mem));
		initial.push_back(f(i, modulo));
		memset(mem, -1, sizeof(mem));
		init.push_back(f(i, mod));
	}
	vector<lli> poly = BerlekampMassey(initial);
	for(lli& x : poly){
		if(x > modulo/2){
			x -= modulo;
			while(x < 0) x += mod;
		}
	}
	cout << rec(poly, init, 3138428376721ll) << "\n";
	return 0;
}