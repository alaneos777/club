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
	vector<string> inv = {"S", "M", "L", "XL", "XXL", "XXXL"};
	map<string, int> mp = {{"S", 0}, {"M", 1}, {"L", 2}, {"XL", 3}, {"XXL", 4}, {"XXXL", 5}};
	vector<int> cnt(6);
	for(int& ci : cnt){
		cin >> ci;
	}
	int n;
	cin >> n;
	int s = n+6, t = n+7;
	flowGraph<int> g(n+8);
	for(int i = 0; i < n; ++i){
		g.addEdge(s, i, 1);
		string sz;
		cin >> sz;
		int pos = sz.find(",");
		if(pos == string::npos){
			g.addEdge(i, n+mp[sz], 1);
		}else{
			string sz1 = sz.substr(0, pos);
			string sz2 = sz.substr(pos+1);
			g.addEdge(i, n+mp[sz1], 1);
			g.addEdge(i, n+mp[sz2], 1);
		}
	}
	for(int i = 0; i < 6; ++i){
		g.addEdge(n+i, t, cnt[i]);
	}
	if(g.dinic(s, t) == n){
		cout << "YES\n";
		for(int i = 0; i < n; ++i){
			for(flowEdge<int> *edge : g.adjList[i]){
				if(edge->dest >= n && edge->flow == 1){
					cout << inv[edge->dest-n] << "\n";
					break;
				}
			}
		}
	}else{
		cout << "NO\n";
	}
	return 0;
}