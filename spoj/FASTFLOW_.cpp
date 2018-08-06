#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli inf = 1ll << 60;

template<typename T>
struct flowEdge{
	int dest;
	T flow, capacity;
	flowEdge *res;
	flowEdge(){
		this->dest = this->flow = this->capacity = 0;
		this->res = NULL;
	}
	flowEdge(int dest, T flow, T capacity){
		this->dest = dest, this->flow = flow, this->capacity = capacity;
		this->res = NULL;
	}
	void addFlow(T flow){
		this->flow += flow;
		this->res->flow -= flow;
	}
};

template<typename T>
struct flowGraph{
	vector<vector<flowEdge<T>*>> adjList;
	vector<int> dist, pos;
	int V;
	flowGraph(int V){
		this->V = V;
		adjList.resize(V);
		dist.resize(V);
		pos.resize(V);
	}
	void addEdge(int u, int v, T flow){
		flowEdge<T> *uv = new flowEdge<T>(v, 0, flow);
		flowEdge<T> *vu = new flowEdge<T>(u, flow, flow);
		uv->res = vu;
		vu->res = uv;
		adjList[u].push_back(uv);
		adjList[v].push_back(vu);
	}
	T edmondsKarp(int s, int t){
		T maxFlow = 0;
		while(true){
			vector<flowEdge<T>*> parent(V);
			queue<int> Q;
			Q.push(s);
			while(!Q.empty() && !parent[t]){
				int u = Q.front(); Q.pop();
				for(flowEdge<T> *v : adjList[u]){
					if(!parent[v->dest] && v->capacity > v->flow){
						parent[v->dest] = v;
						Q.push(v->dest);
					}
				}
			}
			if(!parent[t]) break;
			T f = inf;
			for(int u = t; u != s; u = parent[u]->res->dest)
				f = min(f, parent[u]->capacity - parent[u]->flow);
			for(int u = t; u != s; u = parent[u]->res->dest)
				parent[u]->addFlow(f);
			maxFlow += f;
		}
		return maxFlow;
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int V, E, u, v;
	cin >> V >> E;
	lli c;
	flowGraph<lli> graph(V);
	for(int i = 0; i < E; ++i){
		cin >> u >> v >> c;
		graph.addEdge(u - 1, v - 1, c);
		graph.addEdge(v - 1, u - 1, c);
	}
	cout << graph.edmondsKarp(0, V - 1) << "\n";
	return 0;
}