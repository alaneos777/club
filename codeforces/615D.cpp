#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int m;
	cin >> m;
	map<int, int> fact;
	for(int i = 0; i < m; ++i){
		int pi;
		cin >> pi;
		fact[pi]++;
	}
	bool isSq = true;
	for(const auto & par : fact){
		isSq &= (par.second % 2 == 0);
	}
	if(isSq){
		lli n = 1, divs = 1;
		for(const auto & par : fact){
			n = n * power(par.first, par.second / 2) % mod;
			divs = divs * (par.second + 1) % (mod-1);
		}
		cout << power(n, divs) << "\n";
	}else{
		lli n = 1, divs = 1;
		for(const auto & par : fact){
			n = n * power(par.first, par.second) % mod;
			divs = divs * (par.second + 1) % (2*(mod-1));
		}
		divs /= 2;
		cout << power(n, divs) << "\n";
	}
	return 0;
}