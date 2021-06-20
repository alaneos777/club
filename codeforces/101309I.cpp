#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using piii = pair<pii, int>;
const int inf = 1e9;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	if(fopen("ideal.in", "r")){
		freopen("ideal.in", "r", stdin);
		freopen("ideal.out", "w", stdout);
	}
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int, int>>> adj(n+1);
	for(int i = 0; i < m; ++i){
		int u, v, c;
		cin >> u >> v >> c;
		if(u != v){
			adj[u].emplace_back(v, c);
			adj[v].emplace_back(u, c);
		}
	}
	int start = n, end = 1;
	vector<int> dist(n+1, inf);
	vector<pii> next(n+1);
	vector<piii> q;
	dist[start] = 0;
	q.emplace_back(make_pair(0, 0), start);
	vector<int> idx(n+1);
	while(!q.empty()){
		if(q.front().second == end) break;
		int time = 0;
		vector<piii> new_q;
		for(auto[_, u] : q){
			for(auto[v, c] : adj[u]){
				if(dist[u] + 1 < dist[v]){
					dist[v] = dist[u] + 1;
					next[v] = {u, c};
					idx[v] = new_q.size();
					new_q.emplace_back(make_pair(c, time++), v);
				}else if(dist[u] + 1 == dist[v]){
					if(c < next[v].second){
						next[v] = {u, c};
						new_q[idx[v]].first = {c, time++};
					}
				}
			}
		}
		stable_sort(new_q.begin(), new_q.end(), [&](const piii& a, const piii& b){return a.first < b.first;});
		q = new_q;
	}
	cout << dist[end] << "\n";
	bool first = true;
	while(next[end].first){
		if(first){
			first = false;
		}else{
			cout << " ";
		}
		cout << next[end].second;
		end = next[end].first;
	}
	cout << "\n";
	return 0;
}