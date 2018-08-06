#include <bits/stdc++.h>
using namespace std;

bool kuhn(int u, vector<vector<int>> & adjList, vector<bool> & used, vector<int> & left, vector<int> & right){
	if(used[u]) return false;
	used[u] = true;
	for(int & v : adjList[u]){
		if(right[v] == -1 || kuhn(right[v], adjList, used, left, right)){
			right[v] = u;
			left[u] = v;
			return true;
		}
	}
	return false;
}

int kuhn(vector<vector<int>> & adjList, int l, int r){
	vector<int> left(l, -1), right(r, -1);
	vector<bool> used(l);
	for(int u = 0; u < l; ++u){
		kuhn(u, adjList, used, left, right);
		fill(used.begin(), used.end(), false);
	}
	int ans = 0;
	for(int u = 0; u < r; ++u){
		if(right[u] != -1){
			ans++;
		}
	}
	return ans;
}

int n, m;
int movs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool valid(int x, int y, vector<vector<char>> & grid){
	return 0 <= x && x < n && 0 <= y && y < m && grid[x][y] == '.';
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int caso = 1;
	while(cin >> n >> m && !(n == 0 && m == 0)){
		vector<vector<char>> grid(n, vector<char>(m));
		vector<vector<int>> id(n, vector<int>(m, -1));
		int V = 0;
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				cin >> grid[i][j];
			}
		}
		int l = 0, r = 0;	
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				if(grid[i][j] != '.') continue;
				if(!((i + j) & 1)){
					id[i][j] = l++;
				}else{
					id[i][j] = r++;
				}
			}
		}
		vector<vector<int>> graph(l);
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				if(!((i + j) & 1) && grid[i][j] == '.'){
					for(int k = 0; k < 4; ++k){
						int x = i + movs[k][0];
						int y = j + movs[k][1];
						if(valid(x, y, grid)){
							graph[id[i][j]].push_back(id[x][y]);
						}
					}
				}
			}
		}
		int ans = l + r - 2 * kuhn(graph, l, r);
		if(ans % 2 == 0) ans /= 2;
		else ans = (ans + 1) / 2;
		cout << "Case #" << caso++ << ": " << ans << "\n";
	}
	return 0;
}