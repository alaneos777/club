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

int ans(ull n, vector<ull> & primos){
	int cont = 0;
	for(ull & p : primos){
		if(p * p > n) break;
		while(n % p == 0){
			++cont;
			n /= p;
		}
	}
	if(n > 1){
		++cont;
	}
	return cont;
}

int main(){
	ios_base::sync_with_stdio(0);
	vector<ull> primos;
	criba(1048576, primos);
	int n;
	ull x;
	while(cin >> n){
		int cont = 0;
		for(int i = 1; i <= n; ++i){
			cin >> x;
			if(ans(x, primos) == 2) ++cont;
		}
		cout << cont << "\n";
	}
	return 0;
}