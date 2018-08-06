#include <bits/stdc++.h>
using namespace std;

bool kuhn(int u, vector<vector<int>> & graph, vector<bool> & used, vector<int> & left, vector<int> & right){
	if(used[u]) return false;
	used[u] = true;
	for(int & v : graph[u]){
		if(right[v] == -1 || kuhn(right[v], graph, used, left, right)){
			right[v] = u;
			left[u] = v;
			return true;
		}
	}
	return false;
}

int kuhn(vector<vector<int>> & graph, int l, int r){
	vector<int> left(l, -1), right(r, -1);
	vector<bool> used(l);
	bool found;
	do{
		fill(used.begin(), used.end(), false);
		found = false;
		for(int u = 0; u < l; ++u){
			if(left[u] == -1 && !used[u]){
				found |= kuhn(u, graph, used, left, right);
			}
		}
	}while(found);
	int ans = 0;
	for(int u = 0; u < r; ++u){
		if(right[u] != -1){
			++ans;
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		int l, r, x;
		cin >> l >> r;
		vector<vector<int>> graph(l, vector<int>());
		for(int i = 0; i < l; ++i){
			for(int j = 0; j < r; ++j){
				cin >> x;
				if(x == 1){
					graph[i].push_back(j);
				}
			}
		}
		int ans = kuhn(graph, l, r);
		cout << "Case " << caso << ": a maximum of " << ans << " nuts and bolts can be fitted together\n";
	}
	return 0;
}