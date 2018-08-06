#include <bits/stdc++.h>
using namespace std;

int movs[8][2] = {{1, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool valid(int x, int y, int m, int n){
	return 0 <= x && x < m && 0 <= y && y < n;
}

void dfs(vector<vector<char>> & matrix, vector<vector<bool>> & visited, int x, int y, int m, int n){
	visited[x][y] = true;
	for(int i = 0; i < 8; i++){
		int newX = x + movs[i][0], newY = y + movs[i][1];
		if(valid(newX, newY, m, n) && matrix[newX][newY] == '#' && !visited[newX][newY]){
			dfs(matrix, visited, newX, newY, m, n);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	int m, n;
	cin >> m >> n;
	vector<vector<char>> matrix(m, vector<char>(n));
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			cin >> matrix[i][j];
		}
	}
	int regions = 0;
	vector<vector<bool>> visited(m, vector<bool>(n, false));
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(matrix[i][j] == '#' && !visited[i][j]){
				dfs(matrix, visited, i, j, m, n);
				regions++;
			}
		}
	}
	cout << regions << "\n";
	return 0;
}