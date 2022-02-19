#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

template<typename T>
struct flowEdge{
	int dest;
	T flow, capacity, cost;
	flowEdge *res;

	flowEdge(): dest(0), flow(0), capacity(0), cost(0), res(NULL){}
	flowEdge(int dest, T flow, T capacity, T cost = 0): dest(dest), flow(flow), capacity(capacity), cost(cost), res(NULL){}

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
	void addEdge(int u, int v, T capacity, T cost = 0){
		flowEdge<T> *uv = new flowEdge<T>(v, 0, capacity, cost);
		flowEdge<T> *vu = new flowEdge<T>(u, capacity, capacity, -cost);
		uv->res = vu;
		vu->res = uv;
		adjList[u].push_back(uv);
		adjList[v].push_back(vu);
	}

	//Max Flow Min Cost
	pair<T, T> maxFlowMinCost(int s, int t){
		vector<bool> inQueue(V);
		vector<T> distance(V), cap(V);
		vector<flowEdge<T>*> parent(V);
		T maxFlow = 0, minCost = 0;
		while(true){
			fill(distance.begin(), distance.end(), inf);
			fill(parent.begin(), parent.end(), nullptr);
			fill(cap.begin(), cap.end(), 0);
			distance[s] = 0;
			cap[s] = inf;
			queue<int> Q;
			Q.push(s);
			while(!Q.empty()){
				int u = Q.front(); Q.pop(); inQueue[u] = 0;
				for(flowEdge<T> *v : adjList[u]){
					if(v->capacity > v->flow && distance[v->dest] > distance[u] + v->cost){
						distance[v->dest] = distance[u] + v->cost;
						parent[v->dest] = v;
						cap[v->dest] = min(cap[u], v->capacity - v->flow);
						if(!inQueue[v->dest]){
							Q.push(v->dest);
							inQueue[v->dest] = true;
						}
					}
				}
			}
			if(!parent[t]) break;
			maxFlow += cap[t];
			minCost += cap[t] * distance[t];
			for(int u = t; u != s; u = parent[u]->res->dest)
				parent[u]->addFlow(cap[t]);
		}
		return {maxFlow, minCost};
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<lli> a(n), b(n);
	for(lli& ai : a){
		cin >> ai;
	}
	for(lli& bi : b){
		cin >> bi;
	}
	flowGraph<lli> g(n+3);
	int s = n, t = n+1, t2 = n+2;
	for(int i = 0; i < n; ++i){
		g.addEdge(s, i, 1, a[i]);
		g.addEdge(i, t, 1, b[i]);
		if(i+1 < n) g.addEdge(i, i+1, k, 0);
	}
	g.addEdge(t, t2, k, 0);
	cout << g.maxFlowMinCost(s, t2).second << "\n";
	return 0;
}