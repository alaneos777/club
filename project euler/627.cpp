#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	if(b < 0) b += mod-1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	int M = 30;
	lli N = 10001;

	int d = 10;
	vector<lli> init = {1};
	set<lli> st = {1};
	for(int i = 1; i <= d; ++i){
		set<lli> nxt;
		for(lli x : st){
			for(int y = 1; y <= M; ++y){
				nxt.insert(x*y);
			}
		}
		st = nxt;
		init.push_back(st.size());
		cerr << i << " " << st.size() << "\n";
	}

	lli ans = 0;

	lli a = (d&1) ? mod-1 : 1;
	for(lli num = N-1, den = 1; den <= d; --num, ++den){
		a = a * num % mod * power(den, -1) % mod;
	}

	for(int j = 0; j <= d; ++j){
		(ans += a*init[j]) %= mod;
		a = a * (d-j) % mod * (N-j) % mod * power(j+1, -1) % mod * power(N - (j+1), -1) % mod * (mod-1) % mod;
	}

	cout << ans << "\n";

	return 0;
}