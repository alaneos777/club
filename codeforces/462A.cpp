#include <bits/stdc++.h>
using namespace std;

bool valida(int x, int y, int n){
	return 0 <= x && x < n && 0 <= y && y < n;
}

int main(){
	int n;
	int movs[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
	bool ans = true;
	cin >> n;
	vector< vector<char> > tablero(n, vector<char>(n));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> tablero[i][j];
		}
	}
	for(int i = 0; i < n; i++){
		if(!ans) break;
		for(int j = 0; j < n; j++){
			int acum = 0;
			for(int k = 0; k < 4; k++){
				int nuevo_x = i + movs[k][0];
				int nuevo_y = j + movs[k][1];
				if(valida(nuevo_x, nuevo_y, n)){
					if(tablero[nuevo_x][nuevo_y] == 'o') acum++;
				}
			}
			ans = ans && (acum % 2 == 0);
			if(!ans) break;
		}
	}
	if(ans) cout << "YES";
	else cout << "NO";
	return 0;
}