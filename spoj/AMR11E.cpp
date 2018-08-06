#include <bits/stdc++.h>
using namespace std;

vector<int> factores_primos;

void criba(int n){
	factores_primos.resize(n + 1, 0);
	for(int i = 2; i <= n; i++){
		if(factores_primos[i] == 0){
			for(int j = i; j <= n; j += i){
				factores_primos[j]++;
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(3000);
	vector<int> lucky;
	for(int i = 1; i <= 3000; i++){
		if(factores_primos[i] >= 3) lucky.push_back(i);
	}
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		cout << lucky[n - 1] << "\n";
	}
	return 0;
}