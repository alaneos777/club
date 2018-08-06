#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

vector<vi> graph;
vi mapeo;
int n;

bool tryKuhn(int u, vector<bool> & used, vector<int> & left, vector<int> & right){
	if(used[u]) return false;
	used[u] = true;
	for(int v : graph[u]){
		if(right[v] == -1 || tryKuhn(right[v], used, left, right)){
			right[v] = u;
			left[u] = v;
			return true;
		}
	}
	return false;
}

int maxMatching(int l, int r){
	vector<int> left(l, -1), right(r, -1);
	vector<bool> used(l, false);
	for(int u = 0; u < l; ++u){
		tryKuhn(u, used, left, right);
		fill(used.begin(), used.end(), false);
	}
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
	int u, v, k, r = 0;
	cin >> n;
	graph.resize(n, vi());
	mapeo.resize(n, -1);
	for(int u = 0; u < n; ++u){
		cin >> k;
		for(int i = 0; i < k; ++i){
			cin >> v;
			if(mapeo[v] == -1) mapeo[v] = r++;
			graph[u].push_back(mapeo[v]);
		}
	}
	cout << n - maxMatching(n, r) << "\n";
	return 0;
}