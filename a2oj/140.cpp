#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > divisores;

void criba_divisores(int n){
	divisores.resize(n + 1, vector<int>());
	for(int i = 1; i <= n; i++){
		for(int j = i; j <= n; j += i){
			divisores[j].push_back(i);
		}
	}
}

int ans(int n){
	int minimo = 1e7, suma, a, b, ab;
	for(size_t i = 0; i < divisores[n].size(); i++){
		ab = divisores[n][i];
		for(size_t j = 0; j < divisores[ab].size(); j++){
			a = divisores[ab][j];
			b = ab / a;
			suma = a + b + n / ab;
			if(suma < minimo) minimo = suma;
		}
	}
	return minimo;
}

int main(){
	ios_base::sync_with_stdio(0);
	int t, n;
	cin >> t;
	criba_divisores(500);
	for(int i = 0; i < t; i++){
		cin >> n;
		cout << ans(n) << "\n";
	}
	return 0;
}