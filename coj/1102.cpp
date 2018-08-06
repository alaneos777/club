#include <bits/stdc++.h>
using namespace std;

int main() {
	string linea;
	while(true){
        int suma = 0;
        int mult = 1;
		cin >> linea;
		if(linea == "0") break;
		for(size_t i=0;i<linea.size();i++){
			suma += (linea[i] - '0') * mult;
			mult *= -1;
		}
		cout << linea << " is ";
		if(suma%11 != 0) cout << "not ";
		cout << "a multiple of 11.\n";
	}
	return 0;
}
