#include <bits/stdc++.h>

using namespace std;

struct info_dragon{
	int bonus = 0;
	int requerido = 0;
	bool pasado = false;
};

bool comparador(info_dragon i, info_dragon j){
	return i.bonus > j.bonus;
}

int main(){
	int s, n;
	bool cambio = true, completado = true;
	cin >> s >> n;
	vector<info_dragon> niveles(n);
	for(int i=0; i<n; i++) cin >> niveles[i].requerido >> niveles[i].bonus;
	sort(niveles.begin(), niveles.end(), comparador);
	while(cambio){
		cambio = false;
		for(int i=0; i<n; i++){
			if(!niveles[i].pasado && s > niveles[i].requerido){
				niveles[i].pasado = true;
				s += niveles[i].bonus;
				cambio = true;
				break;
			}
		}
	}
	for(int i=0; i<n; i++){
		if(!niveles[i].pasado){
			completado = false;
			break;
		}
	}
	if(completado) cout << "YES";
	else cout << "NO";
	return 0;
}