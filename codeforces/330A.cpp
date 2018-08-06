#include <bits/stdc++.h>
using namespace std;

int main(){
	int r, c, ans = 0;
	char ij;
	cin >> r >> c;
	vector< vector<int> > mapa(r, vector<int>(c, 0));
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			cin >> ij;
			if(ij == 'S') mapa[i][j] = -1;
			else mapa[i][j] = 1;
		}
	}
	for(int i = 0; i < r; i++){
		int acum = 0;
		for(int j = 0; j < c; j++){
			if(mapa[i][j] == 1){
				acum++;
			}else if(mapa[i][j] == -1){
				acum = -1;
				break;
			}
		}
		if(acum != -1){
			ans += acum;
			for(int j = 0; j < c; j++) mapa[i][j] = 0;
		}
	}
	for(int j = 0; j < c; j++){
		int acum = 0;
		for(int i = 0; i < r; i++){
			if(mapa[i][j] == 1){
				acum++;
			}else if(mapa[i][j] == -1){
				acum = -1;
				break;
			}
		}
		if(acum != -1){
			ans += acum;
			for(int i = 0; i < r; i++) mapa[i][j] = 0;
		}
	}
	cout << ans;
	return 0;
}