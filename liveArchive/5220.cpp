#include <bits/stdc++.h>
using namespace std;

int inf = 1 << 30;

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
	void addEdge(int u, int v, T capacity){
		flowEdge<T> *uv = new flowEdge<T>(v, 0, capacity);
		flowEdge<T> *vu = new flowEdge<T>(u, capacity, capacity);
		uv->res = vu;
		vu->res = uv;
		adjList[u].push_back(uv);
		adjList[v].push_back(vu);
	}
	T blockingFlow(int u, int t, T flow){
		if(u == t) return flow;
		for(int &i = pos[u]; i < adjList[u].size(); ++i){
			flowEdge<T> *v = adjList[u][i];
			if(v->capacity - v->flow > 0 && dist[u] + 1 == dist[v->dest]){
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
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	int caso = 1;
	while(cin >> n && n){
		int s, t, c, u, v, f;
		cin >> s >> t >> c;
		flowGraph<int> graph(n);
		while(c--){
			cin >> u >> v >> f;
			graph.addEdge(u - 1, v - 1, f);
			graph.addEdge(v - 1, u - 1, f);
		}
		cout << "Network " << caso++ << "\nThe bandwidth is " << graph.dinic(s - 1, t - 1) << ".\n\n";
	}
	return 0;
}