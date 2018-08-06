#include <bits/stdc++.h>
using namespace std;
typedef complex<double> comp;
# define M_PI 3.14159265358979323846

int main(){
	ios_base::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--){
		int comandos;
		cin >> comandos;
		comp posicion = 0, direccion = 1;
		double valor;
		while(comandos--){
			string comando;
			cin >> comando >> valor;
			if(comando == "fd"){
				posicion += valor * direccion;
			}else if(comando == "lt"){
				direccion *= polar(1.0, valor * M_PI / 180);
			}else if(comando == "bk"){
				posicion -= valor * direccion;
			}else if(comando == "rt"){
				direccion *= polar(1.0, - valor * M_PI / 180);
			}
		}
		long long int ans = round(abs(posicion));
		cout << ans << "\n";
	}
	return 0;
}