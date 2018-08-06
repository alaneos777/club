#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> graph;
vector<vector<bool>> visited;
int n;

bool valid(int x, int y){
	return 0 <= x && x < n && 0 <= y && y < n && !visited[x][y] && graph[x][y] != '.';
}

int movs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool dfs(int x, int y){
	visited[x][y] = true;
	bool ret = (graph[x][y] == 'x');
	for(int i = 0; i < 4; ++i){
		int newX = x + movs[i][0], newY = y + movs[i][1];
		if(valid(newX, newY)){
			ret |= dfs(newX, newY);
		}
	}
	return ret;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t, caso = 1;
	cin >> t;
	while(t--){
		cin >> n;
		graph = vector<vector<char>>(n, vector<char>(n));
		visited = vector<vector<bool>>(n, vector<bool>(n, false));
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				cin >> graph[i][j];
			}
		}
		int alive = 0;
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				if(valid(i, j)){
					if(dfs(i, j)) ++alive;
				}
			}
		}
		cout << "Case " << caso++ << ": " << alive << "\n";
	}
	return 0;
}