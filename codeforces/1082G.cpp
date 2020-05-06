#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

template<typename T>
struct flowEdge{
	int dest;
	T flow, capacity;
	flowEdge *res;

	flowEdge(): dest(0), flow(0), capacity(0), res(NULL){}
	flowEdge(int dest, T flow, T capacity): dest(dest), flow(flow), capacity(capacity), res(NULL){}

	void addFlow(T flow){
		this->flow += flow;
		this->res->flow -= flow;
	}
};

template<typename T>
struct flowGraph{
	T inf = numeric_limits<T>::max();
	vector<vector<flowEdge<T>*>> adjList;
	vector<int> dist, pos;
	int V;
	flowGraph(int V): V(V), adjList(V), dist(V), pos(V){}
	~flowGraph(){
		for(int i = 0; i < V; ++i)
			for(int j = 0; j < adjList[i].size(); ++j)
				delete adjList[i][j];
	}
	void addEdge(int u, int v, T capacity){
		flowEdge<T> *uv = new flowEdge<T>(v, 0, capacity);
		flowEdge<T> *vu = new flowEdge<T>(u, capacity, capacity);
		uv->res = vu;
		vu->res = uv;
		adjList[u].push_back(uv);
		adjList[v].push_back(vu);
	}

	//Maximun Flow using Dinic Algorithm O(EV^2)
	T blockingFlow(int u, int t, T flow){
		if(u == t) return flow;
		for(int &i = pos[u]; i < adjList[u].size(); ++i){
			flowEdge<T> *v = adjList[u][i];
			if(v->capacity > v->flow && dist[u] + 1 == dist[v->dest]){
				T fv = blockingFlow(v->dest, t, min(flow, v->capacity - v->flow));
				if(fv > 0){
					v->addFlow(fv);
					return fv;
				}
			}
		}
		return 0;
	}
	T dinic(int s, int t){
		T maxFlow = 0;
		dist[t] = 0;
		while(dist[t] != -1){
			fill(dist.begin(), dist.end(), -1);
			queue<int> Q;
			Q.push(s);
			dist[s] = 0;
			while(!Q.empty()){
				int u = Q.front(); Q.pop();
				for(flowEdge<T> *v : adjList[u]){
					if(dist[v->dest] == -1 && v->flow != v->capacity){
						dist[v->dest] = dist[u] + 1;
						Q.push(v->dest);
					}
				}
			}
			if(dist[t] != -1){
				T f;
				fill(pos.begin(), pos.end(), 0);
				while(f = blockingFlow(s, t, inf))
					maxFlow += f;
			}
		}
		return maxFlow;
	}
};

const lli inf = numeric_limits<int>::max();

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> cost(n);
	for(int & ci : cost){
		cin >> ci;
	}
	//s = 0, aristas: [1, ..., m], vertices: [m+1, ..., m+n], t = m+n+1
	flowGraph<lli> G(n + m + 2);
	lli ans = 0;
	for(int i = 1; i <= m; ++i){
		int u, v, w;
		cin >> u >> v >> w;
		ans += w;
		G.addEdge(0, i, w);
		G.addEdge(i, u + m, inf);
		G.addEdge(i, v + m, inf);
	}
	for(int i = 1; i <= n; ++i){
		G.addEdge(i + m, m + n + 1, cost[i - 1]);
	}
	ans -= G.dinic(0, m + n + 1);
	cout << ans << "\n";
	return 0;
}