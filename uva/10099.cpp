#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, r, u, v, p, s, d, t;
	int caso = 1;
	while(cin >> n >> r && n && r){
		vector<vector<int>> graph(n, vector<int>(n));
		for(int i = 0; i < r; ++i){
			cin >> u >> v >> p;
			--u, --v;
			graph[u][v] = graph[v][u] = p;
		}
		cin >> s >> d >> t;
		--s, --d;
		for(int k = 0; k < n; ++k){
			for(int i = 0; i < n; ++i){
				for(int j = 0; j < n; ++j){
					graph[i][j] = max(graph[i][j], min(graph[i][k], graph[k][j]));
				}
			}
		}
		int den = graph[s][d] - 1;
		int ans = t / den;
		if(t % den > 0) ++ans;
		cout << "Scenario #" << caso++ << "\nMinimum Number of Trips = " << ans << "\n\n";
	}
	return 0;
}