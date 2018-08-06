#include <bits/stdc++.h>
using namespace std;

vector< vector<int> > factores_primos;

void criba(int n){
	factores_primos.resize(n + 1, vector<int>());
	for(int i = 2; i <= n; i++){
		if(factores_primos[i].size() == 0){
			for(int j = i; j <= n; j += i){
				factores_primos[j].push_back(i);
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(1000000);
	int t, n;
	cin >> t;
	for(int i = 1; i <= t; i++){
		cin >> n;
		cout << "Case " << i << ": ";
		for(int j = 0; j < factores_primos[n].size(); j++){
			if(j > 0) cout << " ";
			cout << factores_primos[n][j];
		}
		cout << "\n";
	}
	return 0;
}