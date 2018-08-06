#include <iostream>
#include <vector>
using namespace std;

int movs[8][2] = {
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0},
	{1, 1},
	{1, -1},
	{-1, 1},
	{-1, -1}
};

bool validar(int n, int x, int y, vector< vector<char> > & mapa){
	return 0 <= x && x < n && 0 <= y && y < n && mapa[x][y] == '1';
}

void dfs(int n, vector< vector<char> > & mapa, vector< vector<bool> > & visitados, int x, int y){
	visitados[x][y] = true;
	for(int i = 0; i < 8; i++){
		int nuevaX = x + movs[i][0];
		int nuevaY = y + movs[i][1];
		if(validar(n, nuevaX, nuevaY, mapa) && !visitados[nuevaX][nuevaY]){
			dfs(n, mapa, visitados, nuevaX, nuevaY);
		}
	}
}

int main(){
	int n;
	int caso = 1;
	while(cin >> n){
		int componentes = 0;
		vector< vector<char> > mapa(n, vector<char>(n));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cin >> mapa[i][j];
			}
		}
		vector< vector<bool> > visitados(n, vector<bool>(n, false));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(mapa[i][j] == '1' && !visitados[i][j]){
					dfs(n, mapa, visitados, i, j);
					componentes++;
				}
			}
		}
		cout << "Image number " << caso << " contains " << componentes << " war eagles.\n";
		caso++;
	}
	return 0;
}