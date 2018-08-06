#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	int dificultad = 0;
	int ans = 1e7;
	cin >> n;
	vector<int> numeros(n);
	vector<int> diferencias(n - 1);
	for(int i = 0; i < n; i++){
		cin >> numeros[i];
		if(i > 0){
			diferencias[i - 1] = numeros[i] - numeros[i - 1];
			if(diferencias[i - 1] > dificultad) dificultad = diferencias[i - 1];
		}
	}
	for(int i = 0; i < n - 2; i++){
		int suma = diferencias[i] + diferencias[i + 1];
		if(dificultad == diferencias[i] || dificultad == diferencias[i + 1]){
			if(suma < ans) ans = suma;
		}else{
			int tmp = max(suma, dificultad);
			if(tmp < ans) ans = tmp;
		}
	}
	cout << ans;
	return 0;
}