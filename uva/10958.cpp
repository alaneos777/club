#include <bits/stdc++.h>
using namespace std;

typedef long long int ull;

void criba(ull n, vector<ull> & primos){
	vector<bool> es_primo(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	ull limit = sqrt(n);
	for(ull i = 3; i <= limit; i += 2)
		if(es_primo[i])
			for(ull j = i * i; j <= n; j += 2*i)
				es_primo[j] = false;
	primos.push_back(2);
	for(ull i = 3; i <= n; i += 2)
		if(es_primo[i])
			primos.push_back(i);
}

ull divisores(ull n, vector<ull> & primos){
	ull ans = 1;
	for(ull i = 0; i < primos.size(); ++i){
		if(primos[i] * primos[i] > n) break;
		ull pot = 0;
		while(n % primos[i] == 0){
			++pot;
			n /= primos[i];
		}
		ans *= pot + 1;
	}
	if(n > 1) ans *= 2;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	vector<ull> primos;
	criba(sqrt(1e3), primos);
	ull m, n, p;
	int i = 1;
	while(cin >> m >> n >> p && !(m == 0 && n == 0 && p == 0)){
		cout << "Case " << i << ": ";
		if(p == 0) cout << "0\n";
		else cout << (2 * divisores(abs(m * n * p * p), primos) - 1) << "\n";
		++i;
	}
	return 0;
}