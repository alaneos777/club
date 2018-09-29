#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> next(n), costs(n);
	for(int i = 0; i < n; ++i){
		cin >> costs[i];
	}
	for(int i = 0; i < n; ++i){
		cin >> next[i];
		next[i]--;
	}
	vector<int> color(n), cycle;
	function<void(int)> dfs = [&](int u){
		color[u] = 1;
		int v = next[u];
		if(color[v] == 0){
			dfs(v);
		}else if(color[v] == 1){
			int c = v;
			do{
				cycle.push_back(c);
				c = next[c];
			}while(c != v);
		}
		color[u] = 2;
	};
	int ans = 0;
	for(int u = 0; u < n; ++u){
		if(color[u] == 0){
			cycle.clear();
			dfs(u);
			int mini = -1;
			for(int v : cycle){
				if(mini == -1 || costs[v] < mini){
					mini = costs[v];
				}
			}
			if(mini != -1) ans += mini;
		}
	}
	cout << ans << "\n";
	return 0;
}