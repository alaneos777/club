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
		comp pos, dir;
		double valor;
		int signo = 1, incognita = 0, guardarDir = false, guardarPos = false, ignorarDir = false;
		while(comandos--){
			string comando, v;
			cin >> comando >> v;
			if(v == "?"){
				if(comando == "fd"){
					incognita = 1; //longitud
					guardarDir = true;
				}else if(comando == "lt"){
					incognita = 2; //angulo
					guardarPos = true;
					ignorarDir = true;
					signo = 1;
				}else if(comando == "bk"){
					incognita = 1; //longitud
					guardarDir = true;
				}else if(comando == "rt"){
					incognita = 2; //angulo
					guardarPos = true;
					ignorarDir = true;
					signo = -1;
				}
			}else{
				istringstream(v) >> valor;
			}
			if(comando == "fd"){
				if(guardarDir){
					guardarDir = false;
					dir = -direccion;
				}else{
					if(guardarPos){
						pos -= valor * direccion;
					}else{
						posicion += valor * direccion;
					}
				}
			}else if(comando == "lt"){
				if(ignorarDir){
					ignorarDir = false;
				}else{
					direccion *= polar(1.0, valor * M_PI / 180);
				}
			}else if(comando == "bk"){
				if(guardarDir){
					guardarDir = false;
					dir = direccion;
				}else{
					if(guardarPos){
						pos += valor * direccion;
					}else{
						posicion -= valor * direccion;
					}
				}
			}else if(comando == "rt"){
				if(ignorarDir){
					ignorarDir = false;
				}else{
					direccion *= polar(1.0, - valor * M_PI / 180);
				}
			}
		}
		comp ans;
		if(incognita == 1){
			ans = posicion / dir;
			cout << (long long int)round(ans.real());
		}else if(incognita == 2){
			ans = posicion / pos;
			int angulo = round(arg(ans) * 180 / M_PI) * signo;
			angulo = angulo % 360;
			if(angulo < 0) angulo += 360;
			cout << angulo;
		}
		cout << "\n";
	}
	return 0;
}