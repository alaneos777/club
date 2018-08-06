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

vector<pair<int, int>> kuhn(vector<vector<int>> & graph, int l, int r){
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
	vector<pair<int, int>> ans;
	for(int u = 0; u < r; ++u){
		if(right[u] != -1){
			ans.push_back({right[u], u});
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int c, p, a, x;
	while(cin >> c >> p && !(c == 0 && p == 0)){
		vector<int> cardinality(c + 1);
		int l = 0;
		for(int i = 0; i < c; ++i){
			cin >> a;
			l += a;
			cardinality[i + 1] = l;
		}
		vector<vector<int>> graph(l, vector<int>());
		for(int i = 0; i < p; ++i){
			cin >> x;
			for(int j = 0; j < x; ++j){
				cin >> a;
				for(int u = cardinality[a - 1]; u < cardinality[a]; ++u){
					graph[u].push_back(i);
				}
			}
		}
		vector<pair<int, int>> ans = kuhn(graph, l, p);
		sort(ans.begin(), ans.end());
		if(ans.size() == l){
			cout << "1\n";
			for(int i = 0; i < c; ++i){
				for(int u = cardinality[i]; u < cardinality[i + 1]; ++u){
					if(u != cardinality[i]) cout << " ";
					cout << ans[u].second+1;
				}
				cout << "\n";
			}
		}else{
			cout << "0\n";
		}
	}
	return 0;
}