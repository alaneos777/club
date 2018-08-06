#include <iostream>

using namespace std;

int main(){
	int t, n, x, y, actual;
	bool facil, dificil;
	cin >> t;
	for(int i = 0; i < t; i++){
		cin >> n >> x >> y;
		facil = false;
		dificil = false;
		for(int j = 1; j <= n; j++){
			cin >> actual;
			if(j == 1 && actual == x) facil = true;
			if(j == n && actual == y) dificil = true;
		}
		if(facil && dificil){
			cout << "BOTH";
		}else if(facil){
			cout << "EASY";
		}else if(dificil){
			cout << "HARD";
		}else{
			cout << "OKAY";
		}
		cout << "\n";
	}
	return 0;
}