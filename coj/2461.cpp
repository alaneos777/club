#include <bits/stdc++.h>
using namespace std;

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
	T inf = numeric_limits<T>::max();
	flowGraph(int V){
		this->V = V;
		adjList.resize(V);
		dist.resize(V);
		pos.resize(V);
	}
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

struct info{
	int u, v, c;
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0);
	string caso;
	while(getline(cin, caso) && caso != ""){
		int i = 0, j = 0;
		vector<info> edges;
		for(char & c : caso){
			if(c == ' '){
				i++;
				j = 0;
			}else{
				edges.push_back({i, j, c - '0'});
				++j;
			}
		}
		int V = j;
		int ans = numeric_limits<int>::max();
		for(int a = 1; a < V; ++a){
			flowGraph<int> graph(V);
			for(auto & edge : edges){
				graph.addEdge(edge.u, edge.v, edge.c);
			}
			ans = min(ans, graph.dinic(0, a));
		}
		cout << ans << "\n";
	}
	return 0;
}