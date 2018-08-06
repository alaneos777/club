#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

vector<ull> primos;

void criba(ull n){
	primos.push_back(2);
	vector<bool> es_primo(n + 1, true);
	ull limit = sqrt(n);
	for(ull i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(ull j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

void divisores(vector< pair<ull, ull> > & divs, vector< pair<ull, int> > & f, int pos, ull res1, ull res2){
	if(pos == f.size()){
		divs.push_back({res1, res2});
	}else{
		for(int i = 0; i <= f[pos].second; ++i){
			divisores(divs, f, pos + 1, res1, res2);
			res1 *= f[pos].first;
			res2 *= f[pos].first;
			if(i == 0) res2 -= res2 / f[pos].first;
		}
	}
}

void factorizar(ull n, vector< pair<ull, ull> > & ans){
	ull n0 = n;
	vector< pair<ull, int> > f;
	for(ull & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			int pot = 0;
			while(n % p == 0){
				n /= p;
				++pot;
			}
			f.push_back({p, pot});
		}
	}
	if(n > 1){
		f.push_back({n, 1});
	}
	vector< pair<ull, ull> > divs;
	divisores(divs, f, 0, 1, 1);
	sort(divs.rbegin(), divs.rend());
	ull acum = 0;
	ans.resize(divs.size());
	for(int i = 0; i < divs.size(); ++i){
		acum += divs[i].second;
		ans[i] = {divs[divs.size() - 1 - i].first, acum};
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	ull limite = 1000000000000;
	criba(sqrt(limite) + 1);
	int t, q;
	ull n, x;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		cin >> n >> q;
		vector< pair<ull, ull> > ans;
		factorizar(n, ans);
		cout << "Case " << caso << "\n";
		while(q--){
			cin >> x;
			x = min(x, n);
			int i;
			for(i = ans.size() - 1; i >= 0; --i){
				if(x >= ans[i].first){
					cout << ans[i].second << "\n";
					break;
				}
			}
			if(i < 0){
				cout << "0\n";
			}
		}
	}
	return 0;
}