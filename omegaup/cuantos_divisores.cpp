#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

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

ull n_divisores(ull n, vector<ull> & primos){
	ull ans = 1;
	for(ull & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			ull pot = 0;
			while(n % p == 0){
				n /= p;
				++pot;
			}
			ans *= pot + 1;
		}
	}
	if(n > 1){
		ans *= 2;
	}
	return ans;
}

int main(){
	ull n;
	vector<ull> primos;
	cin >> n;
	criba(sqrt(n) + 1, primos);
	cout << n_divisores(n, primos);
	return 0;
}