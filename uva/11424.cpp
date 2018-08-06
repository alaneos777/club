#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

vector<int> primos;

void criba(int n){
	primos.push_back(2);
	vector<bool> es_primo(n + 1, true);
	int limit = sqrt(n);
	for(int i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(int j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

ull suma_gcd(int n){
	int n0 = n;
	ull ans = 1;
	for(int & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			int pot = 0;
			int pi = 1;
			while(n % p == 0){
				n /= p;
				pi *= p;
				++pot;
			}
			ans *= (pi / p) * (1 + (pot + 1) * (p - 1));
		}
	}
	if(n > 1){
		ans *= 1 + 2 * (n - 1);
	}
	return ans - n0;
}

int main(){
	ios_base::sync_with_stdio(0);
	int limite = 200000;
	criba(sqrt(limite) + 1);
	int n;
	ull acum = 0;
	vector<ull> valores(limite + 1);
	for(int i = 1; i <= limite; ++i){
		acum += suma_gcd(i);
		valores[i] = acum;
	}
	while(cin >> n && n != 0){
		ull ans = 0;
		cout << valores[n] << "\n";
	}
	return 0;
}