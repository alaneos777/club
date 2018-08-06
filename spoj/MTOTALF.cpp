#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
int inf = 1 << 30;

vi graph[52];
int cap[52][52], res[52][52], parent[52], mapping[256];

int V = 0;

int updateFlow(int u, int f){
	int p = parent[u];
	if(p == u) return f;
	f = updateFlow(p, min(f, cap[p][u] - res[p][u]));
	res[p][u] += f;
	res[u][p] -= f;
	return f;
}

int addFlow(int s, int t){
	fill(parent, parent + 52, -1);
	queue<int> Q;
	Q.push(s);
	parent[s] = s;
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		if(u == t) break;
		for(int & v : graph[u]){
			if(res[u][v] != cap[u][v] && parent[v] == -1){
				parent[v] = u;
				Q.push(v);
			}
		}
	}
	if(parent[t] == -1) return 0;
	return updateFlow(t, inf);
}

int edmondsKarp(int s, int t){
	int maxFlow = 0, f;
	while(f = addFlow(s, t))
		maxFlow += f;
	return maxFlow;
}

int main(){
	int n;
	scanf("%d", &n);
	char a, b; int f, u, v;
	fill(mapping, mapping + 256, -1);
	for(int i = 0; i < n; ++i){
		scanf(" %c %c %d", &a, &b, &f);
		if(mapping[a] == -1) mapping[a] = V++;
		if(mapping[b] == -1) mapping[b] = V++;
		u = mapping[a], v = mapping[b];
		graph[u].push_back(v);
		graph[v].push_back(u);
		cap[u][v] += f, cap[v][u] += f;
		res[v][u] += f;
	}
	printf("%d\n", edmondsKarp(mapping['A'], mapping['Z']));
	return 0;
}