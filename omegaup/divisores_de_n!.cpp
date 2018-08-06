#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

ull mod = 987654321;

ull pot(ull n, ull p){
	ull ans = 0, div = p;
	while(div <= n){
		ans += n / div;
		div *= p;
	}
	return ans;
}

void criba(ull n, vector<ull> & primos){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
	ull bound = sqrt(n);
	for(ull i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= bound){
				for(ull j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

ull answer(ull n, vector<ull> & primos){
	ull ans = 1;
	for(ull & p : primos){
		if(p > n) break;
		ans = (ans * (pot(n, p) + 1)) % mod;
	}
	return ans;
}

int main(){
	ull n;
	vector<ull> primos;
	criba(1e6, primos);
	cin >> n;
	cout << answer(n, primos);
	return 0;
}