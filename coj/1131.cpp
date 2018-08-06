#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<int> primos;

void criba(int n){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
	int limit = sqrt(n);
	for(int i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(int j = i * i; j <= n; j += 2*i){
					es_primo[j] = false;
				}
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(431);
	vector< vector<int> > factorizaciones(432, vector<int>(primos.size(), 0));
	for(int i = 2; i <= 431; i++){
		factorizaciones[i] = factorizaciones[i - 1];
		for(int j = 0; j < primos.size(); j++){
			int p = primos[j];
			if(p > i) break;
			int pot = 0;
			int i0 = i;
			while(i0 % p == 0){
				i0 /= p;
				++pot;
			}
			factorizaciones[i][j] += pot;
		}
	}
	int n, k;
	while(cin >> n >> k){
		lli ans = 1;
		for(int i = 0; i < primos.size(); i++){
			if(factorizaciones[n][i] == 0) break;
			ans *= factorizaciones[n][i] - factorizaciones[k][i] - factorizaciones[n - k][i] + 1;
		}
		cout << ans << "\n";
	}
	return 0;
}