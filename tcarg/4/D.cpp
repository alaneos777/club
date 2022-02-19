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

int mem[3010][7000];
int mem2[3010][7000];

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	memset(mem, -1, sizeof(mem));
	memset(mem2, -1, sizeof(mem2));
	int n, D;
	cin >> n >> D;
	vector<vector<int>> adj(n);
	for(int i = 1; i < n; ++i){
		int pi;
		cin >> pi;
		adj[pi-1].push_back(i);
	}
	function<int(int, int)> f, g;
	f = [&](int u, int d){
		int& ans = mem[u][d];
		if(ans != -1) return ans;
		ans = 1;
		for(int v : adj[u]){
			ans = (lli)ans * g(v, d) % mod;
		}
		return ans;
	};
	g = [&](int u, int d){
		if(d == 0) return 0;
		int& ans = mem2[u][d];
		if(ans != -1) return ans;
		ans = g(u, d-1) + f(u, d);
		if(ans >= mod) ans -= mod;
		return ans;
	};
	vector<lli> init;
	for(int d = 0; d <= 6500; ++d){
		init.push_back(g(0, d));
	}
	vector<lli> P = BerlekampMassey(init);
	cout << rec(P, init, D) << "\n";
	return 0;
}