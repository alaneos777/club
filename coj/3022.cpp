#include <bits/stdc++.h>
using namespace std;

struct point{
	double x, y;
};

bool tryKuhn(int u, vector<bool> & used, vector<int> & left, vector<int> & right, vector<vector<int>> & adjList){
	if(used[u]) return false;
	used[u] = true;
	for(int & v : adjList[u]){
		if(right[v] == -1 || tryKuhn(right[v], used, left, right, adjList)){
			right[v] = u;
			left[u] = v;
			return true;
		}
	}
	return false;
}

int maxMatching(int l, int r, vector<vector<int>> & graph){
	vector<int> left(l, -1), right(r, -1);
	vector<bool> used(l, false);
	for(int u = 0; u < l; ++u){
		tryKuhn(u, used, left, right, graph);
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

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m, s, v;
	while(cin >> n >> m >> s >> v){
		vector<point> left(n), right(m);
		for(int i = 0; i < n; ++i){
			cin >> left[i].x >> left[i].y;
		}
		for(int j = 0; j < m; ++j){
			cin >> right[j].x >> right[j].y;
		}
		vector<vector<int>> graph(n, vector<int>());
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				if(hypot(left[i].x - right[j].x, left[i].y - right[j].y) <= (double)v*s){
					graph[i].push_back(j);
				}
			}
		}
		cout << n - maxMatching(n, m, graph) << "\n";
	}
	return 0;
}