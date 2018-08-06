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

ull phi(ull n, vector<ull> & primos){
	ull ans = n;
	for(ull & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			while(n % p == 0){
				n /= p;
			}
			ans -= ans / p;
		}
	}
	if(n > 1) ans -= ans / n;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	vector<ull> primos;
	criba(sqrt(1e9), primos);
	ull n;
	while(cin >> n && n != 0){
		cout << phi(n, primos) << "\n";
	}
	return 0;
}