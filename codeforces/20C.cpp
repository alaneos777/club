#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct edge{
	int v;
	lli w;
	edge(int v, lli w): v(v), w(w) {}
	bool operator>(const edge & e) const{
		return w > e.w;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, a, b;
	lli c;
	cin >> n >> m;
	vector<vector<edge>> graph(n);
	for(int i = 0; i < m; ++i){
		cin >> a >> b >> c;
		--a, --b;
		graph[a].emplace_back(b, c);
		graph[b].emplace_back(a, c);
	}

	priority_queue<edge, vector<edge>, greater<edge>> Q;
	vector<int> parent(n, -1);
	vector<lli> cost(n, numeric_limits<lli>::max());

	Q.emplace(0, 0);
	cost[0] = 0;
	parent[0] = -1;
	bool found = false;
	while(!Q.empty()){
		auto source = Q.top(); Q.pop();
		int u = source.v;
		if(u == n-1){
			found = true;
			break;
		}
		for(auto & dest : graph[u]){
			int v = dest.v;
			lli newCost = cost[u] + dest.w;
			if(newCost < cost[v]){
				cost[v] = newCost;
				parent[v] = u;
				Q.emplace(v, newCost);
			}
		}
	}

	if(found){
		deque<int> ans;
		for(int u = n-1; u != -1; u = parent[u]){
			ans.push_front(u + 1);
		}
		for(int u : ans) cout << u << " ";
		cout << "\n";
	}else{
		cout << "-1\n";
	}
	return 0;
}