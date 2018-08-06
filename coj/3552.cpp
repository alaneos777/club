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
	vector<bool> used(l, false);
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
			ans++;
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m, x, y;
	while(cin >> n >> m && !(n == 0 && m == 0)){
		vector<vector<int>> graph(n, vector<int>());
		while(m--){
			cin >> x >> y;
			graph[x].push_back(y);
		}
		cout << kuhn(graph, n, n) << "\n";
	}
	return 0;
}