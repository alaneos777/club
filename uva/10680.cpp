#include <bits/stdc++.h>
using namespace std;

typedef long long int ull;

void criba(ull n, vector<ull> & primos){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
	for(ull i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			for(ull j = i * i; j <= n; j += 2 * i){
				es_primo[j] = false;
			}
		}
	}
}

ull LCM_N(ull n, vector<ull> & primos){
	ull ans = 1;
	ull dos = 0, cinco = 0, diez;
	for(ull i = 0; i < primos.size(); ++i){
		ull p = primos[i];
		if(p > n) break;
		ull mult = p;
		if(p == 2) ++dos;
		if(p == 5) ++cinco;
		while(mult * p <= n){
			mult *= p;
			if(p == 2) ++dos;
			if(p == 5) ++cinco;
		}
		if(p != 2 && p != 5) ans = (ans * mult) % 10;
	}
	diez = min(dos, cinco);
	dos -= diez;
	cinco -= diez;
	for(ull i = 1; i <= dos; ++i) ans = (ans * 2) % 10;
	for(ull i = 1; i <= cinco; ++i) ans = (ans * 5) % 10;
	return ans;
}

int main(){
	ull maximo = 1e6;
	ios_base::sync_with_stdio(0);
	vector<ull> primos;
	criba(maximo, primos);
	ull n;
	while(cin >> n && n != 0){
		cout << LCM_N(n, primos) << "\n";
	}
	return 0;
}