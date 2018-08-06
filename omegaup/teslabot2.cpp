#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct planet{
	lli x, y, z;
	int p, q;
};

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct flowEdge{
    int dest;
    T flow, capacity, cost;
    flowEdge *res;
    flowEdge(){
        this->dest = this->flow = this->capacity = this->cost = 0;
        this->res = NULL;
    }
    flowEdge(int dest, T flow, T capacity, T cost = 0){
        this->dest = dest, this->flow = flow, this->capacity = capacity, this->cost = cost;
        this->res = NULL;
    }
    void addFlow(T flow){
        this->flow += flow;
        this->res->flow -= flow;
    }
};

template<typename T>
struct flowGraph{
    T inf = numeric_limits<T>::max();
    vector<vector<flowEdge<T>*>> adjList;
    int V;
    flowGraph(int V){
        this->V = V;
        adjList.resize(V);
    }
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
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	vector<planet> planets(n + 1);
	int c1 = 0, c2 = 0;
	for(int i = 1; i <= n; ++i){
		cin >> planets[i].x >> planets[i].y >> planets[i].z >> planets[i].p >> planets[i].q;
		c1 += planets[i].p;
		c2 += planets[i].q;
	}
	if(c1 != c2){
		cout << "Imposible";
		return 0;
	}
    flowGraph<lli> graph(2 * n + 2);
	for(int i = 1; i <= n; ++i)
		graph.addEdge(0, i, planets[i].p, 0);
	for(int a = 1; a <= n; ++a)
		for(int b = 1; b <= n; ++b)
			if(a != b)
				graph.addEdge(a, n + b, 1, planets[a].x * planets[b].z * planets[b].z + planets[a].y * planets[a].y * planets[b].y + planets[a].z * planets[b].x * planets[b].x);
	for(int i = 1; i <= n; ++i)
		graph.addEdge(n + i, 2 * n + 1, planets[i].q, 0);
	auto Ans = graph.maxFlowMinCost(0, 2 * n + 1);
    lli maxFlow = Ans.first, minCost = Ans.second;
	if(maxFlow != c1){
		cout << "Imposible";
		return 0;
	}
	cout << minCost << "\n";
	for(int u = 1; u <= n; ++u){
		for(flowEdge<lli> *v : graph.adjList[u]){
			if(v->dest > 0 && v->flow == 1){
				cout << u << " " << (v->dest  - n) << " " << v->cost << "\n";
			}
		}
	}
	return 0;
}