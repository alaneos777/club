#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long double ld;
typedef vector<ld> tupla;
typedef vector<tupla> matriz;

bool isZero(ld x){
	return abs(x) < 1e-9;
}

void tipo1(tupla & f1, ld k){
	for(int i = 0; i < f1.size(); i++){
		f1[i] /= k;
	}
}

void tipo2(tupla & f1, tupla & f2){
	swap(f1, f2);
}

void tipo3(tupla & f1, tupla & f2, ld k){
	for(int i = 0; i < f1.size(); i++){
		f1[i] += k * f2[i];
	}
}

bool Invertir(matriz & A, matriz & ans){
	int m = A.size();
	int n = A[0].size();
	int i = 0, j = 0;
	while(i < m && j < n){
		ld maximo = 0;
		ld inv;
		int fila = -1;
		/*for(int k = i; k < m; k++){
			if(abs(A[k][j]) > maximo){
				maximo = abs(A[k][j]);
				fila = k;
			}
		}*/
		if(!isZero(A[i][j])){
			/*tipo2(A[i], A[fila]);
			tipo2(ans[i], ans[fila]);*/
			inv = A[i][j];
			tipo1(A[i], inv);
			tipo1(ans[i], inv);
			for(int k = 0; k < m; k++){
				if(k != i){
					inv = -A[k][j];
					tipo3(A[k], A[i], inv);
					tipo3(ans[k], ans[i], inv);
				}
			}
			i++;
		}else{
			return false;
		}
		j++;
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(0);
	int n;
	while(cin >> n && n != 0){
		matriz A(n, tupla(n));
		matriz ans(n, tupla(n));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cin >> A[i][j];
			}
			ans[i][i] = 1;
		}
		if(Invertir(A, ans)){
			for(int i = 0; i < n; i++){
				for(int j = 0; j < n; j++){
					if(j > 0) cout << " ";
					cout << fixed << setprecision(6) << ans[i][j];
				}
				cout << "\n";
			}
		}else{
			cout << "Not possible\n";
		}
		cout << "\n";
	}
	return 0;
}