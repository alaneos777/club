#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;

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

//Finds the shortest linear recurrence relation for the
//given init values. Only works for prime modulo.
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
	return cur;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<lli> a(n);
	bool zero = true;
	for(lli& ai : a){
		cin >> ai;
		zero &= ai==0;
	}
	vector<lli> c = n==0 || zero ? vector<lli>() : BerlekampMassey(a);
	cout << c.size() << "\n";
	for(lli ci : c){
		cout << ci << " ";
	}
	if(n) cout << "\n";
	return 0;
}