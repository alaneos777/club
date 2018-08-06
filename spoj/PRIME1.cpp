#include <bits/stdc++.h>
using namespace std;

vector<int> primos;
vector<bool> es_primo;

void criba(int n){
	es_primo.resize(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	primos.push_back(2);
	for(int i = 4; i <= n; i += 2) es_primo[i] = false;
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

bool isPrime(int n){
	if(n <= 31623){
		return es_primo[n];
	}else{
		for(int & p : primos){
			if(p * p > n) break;
			if(n % p == 0) return false;
		}
		return true;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(31623);
	int t;
	cin >> t;
	while(t--){
		int m, n;
		cin >> m >> n;
		for(int i = m; i <= n; i++){
			if(isPrime(i)) cout << i << "\n";
		}
		if(t > 0) cout << "\n";
	}
	return 0;
}