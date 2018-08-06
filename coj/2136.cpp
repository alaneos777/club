#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
int inf = 2e9+1;

int gcd(int a, int b){
	int r;
	while(b) r = a % b, a = b, b = r;
	return a;
}

int blockingFlow(int u, int t, int f, vii & graph, vii & cap, vii & res, vi & dist){
	if(u == t) return f;
	int flow = 0;
	for(int & v : graph[u]){
		if(flow == f) break;
		if(dist[u] + 1 <= dist[v]){
			int fv = blockingFlow(v, t, min(f - flow, cap[u][v] - res[u][v]), graph, cap, res, dist);
			res[u][v] += fv;
			flow += fv;
			res[v][u] -= fv;
		}
	}
	return flow;
}

int dinic(int s, int t, vii & graph, vii & cap, vii & res){
	vector<int> dist(graph.size());
	int maxFlow = 0;
	while(dist[t] < inf){
		fill(dist.begin(), dist.end(), inf);
		queue<int> Q;
		Q.push(s);
		dist[s] = 0;
		while(!Q.empty()){
			int u = Q.front(); Q.pop();
			for(int & v : graph[u]){
				if(res[u][v] != cap[u][v] && dist[v] > dist[u] + 1){
					dist[v] = dist[u] + 1;
					Q.push(v);
				}
			}
		}
		if(dist[t] < inf) maxFlow += blockingFlow(s, t, inf, graph, cap, res, dist);
	}
	return maxFlow;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	int minimo = 2e9+1, maximo = 0, s, t;
	vector<int> nums(n);
	for(int i = 0; i < n; ++i){
		cin >> nums[i];
		if(nums[i] < minimo){
			minimo = nums[i];
			s = i;
		}
		if(nums[i] > maximo){
			maximo = nums[i];
			t = i;
		}
	}
	vector<vector<int>> graph(n, vector<int>());
	vector<vector<int>> cap(n, vector<int>(n));
	vector<vector<int>> res(n, vector<int>(n));
	for(int i = 0; i < n - 1; ++i){
		for(int j = i + 1; j < n; ++j){
			int d = gcd(nums[i], nums[j]);
			if(d > 1){
				graph[i].push_back(j);
				graph[j].push_back(i);
				cap[i][j] = cap[j][i] = 2*d;
				res[i][j] = res[j][i] = d;
			}
		}
	}
	cout << dinic(s, t, graph, cap, res) << "\n";
	return 0;
}