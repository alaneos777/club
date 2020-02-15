#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> sieve(int n){
	vector<int> lp(n+1);
	iota(lp.begin(), lp.end(), 0);
	for(int i = 2; i*i <= n; ++i){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += i){
				if(lp[j] == j){
					lp[j] = i;
				}
			}
		}
	}
	return lp;
}

const int M = 1e7;
const auto lp = sieve(M);

int main(){
	map<pair<int, int>, int> posible;
	for(int i = 2; i <= M; ++i){
		int n = i;
		map<int, int> f;
		while(n > 1){
			int p = lp[n];
			int pot = 0;
			while(n % p == 0) n /= p, pot++;
			f[p] = pot;
		}
		if(f.size() == 2){
			auto it = f.begin();
			int p = it->first; ++it;
			int q = it->first;
			posible[{p, q}] = i;
		}
	}
	lli ans = 0;
	for(auto par : posible){
		ans += par.second;
	}
	cout << ans << "\n";
	return 0;
}