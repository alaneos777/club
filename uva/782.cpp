#include <bits/stdc++.h>
using namespace std;

int m, n;
vector<vector<char>> grid;
vector<vector<bool>> visited;

int movs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool valid(int x, int y){
	return 0 <= x && x < m && 0 <= y && y < n && !visited[x][y] && grid[x][y] == ' ';
}

bool valid2(int x, int y){
	return 0 <= x && x < m && 0 <= y && y < n && grid[x][y] == '*';
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	string str;
	getline(cin, str);
	int t;
	stringstream(str) >> t;
	while(t--){
		m = n = 0;
		vector<string> lines;
		while(getline(cin, str) && !(str.size() && str[0] == '_')){
			lines.push_back(str);
			n = max(n, (int)str.size());
			++m;
		}
		string sep = str;
		++n;
		grid = vector<vector<char>>(m,	vector<char>(n, ' '));
		for(int i = 0; i < m; ++i){
			for(int j = 0; j < lines[i].size(); ++j){
				grid[i][j] = lines[i][j];
			}
		}
		visited = vector<vector<bool>>(m, vector<bool>(n, false));
		int x0 = 0, y0 = 0;
		char letter = 'X';
		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				if(grid[i][j] == '*'){
					x0 = i, y0 = j;
				}else if(grid[i][j] != ' '){
					letter = grid[i][j];
				}
			}
		}
		queue<pair<int, int>> Q;
		Q.push({x0, y0});
		while(!Q.empty()){
			pair<int, int> current = Q.front(); Q.pop();
			int x = current.first, y = current.second;
			visited[x][y] = true;
			for(int i = 0; i < 4; ++i){
				int newX = x + movs[i][0], newY = y + movs[i][1];
				if(valid(newX, newY)){
					grid[newX][newY] = '*';
					visited[newX][newY] = true;
					Q.push({newX, newY});
				}
			}
		}
		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				if(grid[i][j] == letter){
					for(int k = 0; k < 4; ++k){
						int newX = i + movs[k][0], newY = j + movs[k][1];
						if(valid2(newX, newY)){
							grid[newX][newY] = '#';
						}
					}
				}
			}
		}
		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				if(grid[i][j] == '*') grid[i][j] = ' ';
			}
			while(grid[i].size() && grid[i].back() == ' ') grid[i].pop_back();
			for(int j = 0; j < grid[i].size(); ++j){
				cout << grid[i][j];
			}
			cout << "\n";
		}
		cout << sep << "\n";
	}
	return 0;
}