#include <bits/stdc++.h>
using namespace std;

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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int l, r, m;
	cin >> l >> r >> m;
	flowGraph<int> graph(l+r+2);
	for(int i = 0; i < m; ++i){
		int u, v;
		cin >> u >> v;
		graph.addEdge(u, l+v, 1);
	}
	for(int u = 0; u < l; ++u){
		graph.addEdge(l+r, u, 1);
	}
	for(int v = 0; v < r; ++v){
		graph.addEdge(l+v, l+r+1, 1);
	}
	int k = graph.dinic(l+r, l+r+1);
	cout << k << "\n";
	for(int u = 0; u < l; ++u){
		for(auto dest : graph.adjList[u]){
			if(dest->flow == 1 && dest->dest - l < r){
				cout << u << " " << dest->dest - l << "\n";
			}
		}
	}
	return 0;
}