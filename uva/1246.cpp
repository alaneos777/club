#include <bits/stdc++.h>
using namespace std;

void criba_primos(int n, vector<bool> & es_primo){
	es_primo.resize(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	for(int i = 4; i <= n; i += 2){
		es_primo[i] = false;
	}
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2){
		if(es_primo[i]){
			for(int j = i * i; j <= n; j += 2 * i){
				es_primo[j] = false;
			}
		}
	}
}

void criba_divisores(int n, vector<int> & n_divisores){
	n_divisores.resize(n + 1, 0);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			n_divisores[j]++;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	vector<bool> es_primo;
	vector<int> n_divisores;
	criba_primos(1000, es_primo);
	criba_divisores(10000, n_divisores);
	int t, l, h;
	cin >> t;
	while(t--){
		cin >> l >> h;
		bool exists = false;
		bool first = true;
		for(int i = l; i <= h; ++i){
			if(es_primo[n_divisores[i]]){
				exists = true;
				if(first){
					first = false;
				}else{
					cout << " ";
				}
				cout << i;
			}
		}
		if(!exists){
			cout << "-1";
		}
		cout << "\n";
	}
	return 0;
}