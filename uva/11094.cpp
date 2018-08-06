#include <bits/stdc++.h>
using namespace std;

int m, n, x_0, y_0;
char c;

bool valid(int x, int y){
	return 0 <= x && x < m && 0 <= y && y < n;
}

int movs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool dfs(int i, int j, vector<vector<char>> & graph, vector<vector<bool>> & visited, int & count){
	count++;
	visited[i][j] = true;
	bool inside = (x_0 == i && y_0 == j);
	for(int m = 0; m < 4; m++){
		int newI = i + movs[m][0], newJ = (j + movs[m][1]) % n;
		if(newJ < 0) newJ += n;
		if(valid(newI, newJ) && graph[newI][newJ] == c && !visited[newI][newJ]){
			inside |= dfs(newI, newJ, graph, visited, count);
		}
	}
	return inside;
}

int main(){
	ios_base::sync_with_stdio(0);
	while(cin >> m >> n){
		vector<vector<char>> graph(m, vector<char>(n));
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				cin >> graph[i][j];
			}
		}
		cin >> x_0 >> y_0;
		c = graph[x_0][y_0];
		int ans = 0;
		vector<vector<bool>> visited(m, vector<bool>(n, false));
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				int count = 0;
				if(graph[i][j] == c && !visited[i][j]){
					if(!dfs(i, j, graph, visited, count)){
						ans = max(ans, count);
					}
				}
			}
		}
		cout << ans << "\n";
	}
	return 0;
}