#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

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

struct point{
	double x, y;
	int n, m;
	double dist(const point & p){
		return hypot(x - p.x, y - p.y);
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n, c, m;
		int total = 0;
		double d, x, y;
		cin >> n >> d;
		flowGraph<int> graph(2*n + 1);
		vector<point> points(n);
		for(int i = 1; i <= n; ++i){
			cin >> x >> y >> c >> m;
			total += c;
			points[i - 1] = {x, y, c, m};
			graph.addEdge(0, 2 * i - 1, c);
			graph.addEdge(2 * i - 1, 2 * i, m);
		}
		vector<pair<int, int>> valid;
		for(int i = 0; i < n - 1; ++i){
			for(int j = i + 1; j < n; ++j){
				if(points[i].dist(points[j]) <= d){
					valid.push_back({i + 1, j + 1});
				}
			}
		}
		vector<int> ans;
		for(int u = 1; u <= n; ++u){
			flowGraph<int> graph(2*n + 1);
			for(int j = 1; j <= n; ++j){
				graph.addEdge(0, 2 * j - 1, points[j - 1].n);
				graph.addEdge(2 * j - 1, 2 * j, points[j - 1].m);
			}
			for(auto & par : valid){
				int i = par.first, j = par.second;
				graph.addEdge(2 * i, 2 * j - 1, graph.inf);
				graph.addEdge(2 * j, 2 * i - 1, graph.inf);
			}
			if(graph.dinic(0, 2 * u - 1) == total){
				ans.push_back(u - 1);
			}
		}
		if(ans.size() == 0){
			cout << "-1\n";
		}else{
			for(int i = 0; i < ans.size(); ++i){
				if(i) cout << " ";
				cout << ans[i];
			}
			cout << "\n";
		}
	}
	return 0;
}