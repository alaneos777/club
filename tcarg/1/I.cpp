#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using tup = tuple<int, int, int, int>;

bool vis[1010][1010][4][4];

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, x0, y0;
	cin >> n >> m;
	vector<vector<char>> grid(n, vector<char>(m));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			cin >> grid[i][j];
			if(grid[i][j] == 'S'){
				x0 = i;
				y0 = j;
			}
		}
	}
	vector<pair<int, int>> movs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	auto valid = [&](int x, int y){
		return 0 <= x && x < n && 0 <= y && y < m && (grid[x][y] == '.' || grid[x][y] == 'T');
	};
	auto isvis = [&](const tup& t){
		auto[x, y, dir, turns] = t;
		return vis[x][y][dir][turns];
	};
	auto markVis = [&](const tup& t){
		auto[x, y, dir, turns] = t;
		vis[x][y][dir][turns] = true;
	};

	queue<tup> q;
	for(int i = 0; i < 4; ++i){
		tup t = {x0, y0, i, 0};
		q.emplace(t);
		markVis(t);
	}
	bool found = false;
	while(!q.empty()){
		auto[x, y, dir, turns] = q.front(); q.pop();
		if(grid[x][y] == 'T'){
			found = true;
			break;
		}
		for(int i = 0; i < 4; ++i){
			int nturns = turns;
			if(movs[dir] != movs[i]) nturns++;
			if(nturns > 2) continue;
			auto[dx, dy] = movs[i];
			int nx = x + dx, ny = y + dy;
			tup nt = {nx, ny, i, nturns};
			if(valid(nx, ny) && !isvis(nt)){
				q.push(nt);
				markVis(nt);
			}
		}
	}
	if(found){
		cout << "YES\n";
	}else{
		cout << "NO\n";
	}
	return 0;
}