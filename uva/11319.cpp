#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef unsigned long long int ull;

typedef vector<ld> tupla;
typedef vector<tupla> matriz;

void dividirFilaPorEscalar(matriz & A, int k, ld c){
	for(int j = 0; j < A[k].size(); j++){
		A[k][j] = A[k][j] / c;
	}
}

void intercambiarFilas(matriz & A, int i, int k){
	swap(A[i], A[k]);
}

void sumarMultiploEscalar(matriz & A, int k, int l, ld c){
	for(int j = 0; j < A[k].size(); j++){
		A[k][j] += c * A[l][j];
	}
}

void gauss(matriz & A){
	int m = A.size();
	int n = A[0].size() - 1;
	int i = 0, j = 0;
	while(i < m && j < n){
		ld largest = 0;
		int mayor = -1;
		for(int k = i; k < m; k++){
			if(abs(A[k][j]) > largest){
				largest = A[k][j];
				mayor = k;
			}
		}
		intercambiarFilas(A, i, mayor);
		dividirFilaPorEscalar(A, i, A[i][j]);
		for(int k = 0; k < m; k++){
			if(k != i){
				sumarMultiploEscalar(A, k, i, -A[k][j]);
			}
		}
		i++;
		j++;
	}
}

ull evaluar(vector<ld> & polinomio, ull x0){
	ull ans = 0;
	for(int i = polinomio.size() - 1; i >= 0; i--){
		ans = ans * x0 + (int)polinomio[i];
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	matriz A(7, tupla(7, 1));
	for(int i = 0; i < 7; i++){
		for(int j = 1; j < 7; j++){
			A[i][j] = A[i][j - 1] * (i + 1);
		}
	}
	int n;
	cin >> n;
	while(n--){
		vector<ull> numeros(1500);
		matriz B = A;
		vector<ld> polinomio(7, 0);
		for(int i = 0; i < 1500; i++){
			cin >> numeros[i];
		}
		for(int i = 0; i < 7; i++){
			B[i].push_back(numeros[i]);
		}
		gauss(B);
		bool test = true;
		for(int i = 0; i < 7; i++){
			polinomio[i] = round(B[i][7]);
			test &= (0 <= polinomio[i] && polinomio[i] < 1001);
		}
		if(test){
			for(int i = 0; i < 1500; i++){
				if(evaluar(polinomio, i + 1) != numeros[i]){
					test = false;
					break;
				}
			}
		}
		if(test){
			for(int i = 0; i < 7; i++){
				if(i > 0) cout << " ";
				cout << (int)polinomio[i];
			}
		}else{
			cout << "This is a smart sequence!";
		}
		cout << "\n";
	}
	return 0;
}