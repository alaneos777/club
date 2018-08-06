#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<lli> primos;

void criba(lli n){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(lli j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

void factorizar(lli n){
	for(lli & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			lli pot = 0;
			while(n % p == 0){
				n /= p;
				pot++;
			}
			cout << p << "^" << pot << " ";
		}
	}
	if(n > 1) cout << n << "^1";
	cout << "\n";
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(31622777);
	lli n;
	while(true){
		cin >> n;
		if(n == 0) break;
		factorizar(n);
	}
	return 0;
}