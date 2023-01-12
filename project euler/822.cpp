#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;
using tup = tuple<ld, int, lli>;

const lli mod = 1234567891;

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans*a % m;
		b >>= 1;
		a = a*a % m;
	}
	return ans;
}

lli process(const set<tup>& st){
	lli ans = 0;
	for(auto[val, k, t] : st){
		ans += power(k, power(2, t, mod-1), mod);
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

lli S(int n, lli m){
	set<tup> st;
	for(int k = 2; k <= n; ++k){
		st.emplace(log2l(log2l(k)), k, 0);
	}
	for(int i = 1; i <= 2*(n-1) && m > 0; ++i, --m){
		auto[val, k, t] = *st.begin();
		st.erase(st.begin());
		st.emplace(val+1, k, t+1);
	}
	if(m == 0) return process(st);
	lli q = m/(n-1), r = m%(n-1);
	set<tup> st2;
	int idx = 1;
	for(auto[val, k, t]: st){
		t += q, val += q;
		if(idx <= r) t++, val++;
		idx++;
		st2.emplace(val, k, t);
	}
	return process(st2);
}

int main(){
	cout << S(1e4, 1e16) << "\n";
	return 0;
}