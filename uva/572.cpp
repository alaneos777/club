#include <bits/stdc++.h>
using namespace std;

int movs[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

int m, n;
vector<vector<char>> graph;
vector<vector<bool>> visited;

bool valid(int x, int y){
	return 0 <= x && x < m && 0 <= y && y < n && graph[x][y] == '@' && !visited[x][y];
}

void dfs(int x, int y){
	visited[x][y] = true;
	for(int i = 0; i < 8; ++i){
		int newX = x + movs[i][0];
		int newY = y + movs[i][1];
		if(valid(newX, newY)) dfs(newX, newY);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	while(cin >> m >> n){
		if(m == 0) break;
		graph = vector<vector<char>>(m, vector<char>(n));
		visited = vector<vector<bool>>(m, vector<bool>(n, false));
		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				cin >> graph[i][j];
			}
		}
		int comps = 0;
		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				if(valid(i, j)){
					dfs(i, j);
					++comps;
				}
			}
		}
		cout << comps << "\n";
	}
	return 0;
}