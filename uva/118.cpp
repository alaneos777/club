#include <bits/stdc++.h>
using namespace std;

bool validar(int m, int n, int x, int y){
	return 0 <= x && x <= m && 0 <= y && y <= n;
}

char getOrientacion(int a, int b){
	if(a == 0 && b == 1){
		return 'N';
	}else if(a == 0 && b == -1){
		return 'S';
	}else if(a == 1 && b == 0){
		return 'E';
	}else if(a == -1 && b == 0){
		return 'W';
	}
}

int main(){
	int m, n, x, y, tmp;
	char orientacion;
	string movs;
	cin >> m >> n;
	int a, b;
	vector< vector<bool> > mapa(m + 1, vector<bool>(n + 1, false));
	while(cin >> x >> y >> orientacion){
		bool lost = false;
		switch(orientacion){
			case 'N':{a = 0; b = 1; break;}
			case 'S':{a = 0; b = -1; break;}
			case 'E':{a = 1; b = 0; break;}
			case 'W':{a = -1; b = 0; break;}
		}
		cin >> movs;
		for(char mov : movs){
			if(!lost){
				switch(mov){
					case 'L':{
						tmp = a;
						a = -b;
						b = tmp;
						break;
					}
					case 'R':{
						tmp = a;
						a = b;
						b = -tmp;
						break;
					}
					case 'F':{
						if(validar(m, n, x + a, y + b)){
							x += a;
							y += b;
						}else{
							if(!mapa[x][y]){
								mapa[x][y] = true;
								lost = true;
							}
						}
						break;
					}
				}
			}
		}
		cout << x << " " << y << " " << getOrientacion(a, b);
		if(lost){
			cout << " LOST";
		}
		cout << "\n";
	}
	return 0;
}