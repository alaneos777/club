#include <bits/stdc++.h>
using namespace std;

bool validar(int m, int n, int x, int y){
	return 0 <= x && x < m && 0 <= y && y < n;
}

struct info{
	int costo, x, y;
};

struct comparador{
	bool operator() (const info & a, const info & b) const{
		if(a.costo == b.costo){
			if(a.x == b.x){
				return a.y > b.y;
			}else{
				return a.x > b.x;
			}
		}else{
			return a.costo > b.costo;
		}
	}
};

int movs[4][2] = {
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1}
};

int inf = 1e9;

int answer(int m, int n, vector< vector<int> > & mapa){
	vector< vector<bool> > visitados(m, vector<bool>(n, false));
	vector< vector<int> > costos(m, vector<int>(n, inf));
	priority_queue<info, vector<info>, comparador> cola;
	//set<info, comparador> cola;
	cola.push({mapa[0][0], 0, 0});
	//cola.insert({mapa[0][0], 0, 0});
	costos[0][0] = mapa[0][0];
	while(!cola.empty()){
		info actual = cola.top();
		//info actual = *cola.begin();
		cola.pop();
		if(visitados[actual.x][actual.y]) continue;
		//cola.erase(cola.begin());
		visitados[actual.x][actual.y] = true;
		if(actual.x == (m - 1) && actual.y == (n - 1)){
			return actual.costo;
		}
		for(int i = 0; i < 4; ++i){
			int nuevaX = actual.x + movs[i][0];
			int nuevaY = actual.y + movs[i][1];
			if(validar(m, n, nuevaX, nuevaY) && !visitados[nuevaX][nuevaY]){
				int nuevo = costos[actual.x][actual.y] + mapa[nuevaX][nuevaY];
				if(nuevo < costos[nuevaX][nuevaY]){
					cola.push({nuevo, nuevaX, nuevaY});
					//cola.erase({costos[nuevaX][nuevaY], nuevaX, nuevaY});
					//cola.insert({nuevo, nuevaX, nuevaY});
					costos[nuevaX][nuevaY] = nuevo;
				}
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	int casos, m, n;
	cin >> casos;
	for(int t = 0; t < casos; ++t){
		cin >> m >> n;
		vector< vector<int> > mapa(m, vector<int>(n));
		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				cin >> mapa[i][j];
			}
		}
		cout << answer(m, n, mapa) << "\n";
	}
	return 0;
}