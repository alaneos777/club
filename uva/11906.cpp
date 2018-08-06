#include <bits/stdc++.h>
using namespace std;

int r, c, m, n, w;
int even, odd;

vector<vector<bool>> graph;
vector<vector<bool>> visited;
vector<pair<int, int>> movs;

bool valid(int x, int y){
	return 0 <= x && x < r && 0 <= y && y < c && graph[x][y];
}

void dfs(int x, int y){
	visited[x][y] = true;
	int count = 0;
	for(int i = 0; i < movs.size(); ++i){
		int nx = x + movs[i].first, ny = y + movs[i].second;
		if(valid(nx, ny)){
			++count;
			if(!visited[nx][ny]) dfs(nx, ny);
		}
	}
	if(count & 1) ++odd;
	else ++even;
}

int main(){
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; caso++){
		cin >> r >> c >> m >> n >> w;
		graph = vector<vector<bool>>(r, vector<bool>(c, true));
		visited = vector<vector<bool>>(r, vector<bool>(c, false));
		while(w--){
			int x, y;
			cin >> x >> y;
			graph[x][y] = false;
		}
		movs = {{m, n}, {-m, n}, {m, -n}, {-m, -n}, {n, m}, {-n, m}, {n, -m}, {-n, -m}};
		sort(movs.begin(), movs.end());
		movs.erase(unique(movs.begin(), movs.end()), movs.end());
		odd = 0, even = 0;
		dfs(0, 0);
		cout << "Case " << caso << ": " << even << " " << odd << "\n";
	}
	return 0;
}