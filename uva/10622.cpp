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

ull max_power(ull n, vector<ull> & primos){
	bool neg = (n < 0);
	n = abs(n);
	ull ans = 0;
	for(ull & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			ull pot = 0;
			while(n % p == 0){
				++pot;
				n /= p;
			}
			if(neg){
				while(pot % 2 == 0){
					pot /= 2;
				}
			}
			ans = __gcd(ans, pot);
		}
	}
	if(n > 1){
		ans = 1;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	vector<ull> primos;
	criba(46341, primos);
	ull x;
	while(cin >> x && x != 0){
		cout << max_power(x, primos) << "\n";
	}
	return 0;
}