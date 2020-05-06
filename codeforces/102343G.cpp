#include <bits/stdc++.h>
using namespace std;

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

inline int in(int id){
	return 2*id + 1;
}
inline int out(int id){
	return 2*id + 2;
}

vector<pair<int, int>> movs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int r, c;
	cin >> r >> c;
	vector<vector<char>> grid(r, vector<char>(c));
	//id original = c*i + j
	//ids duplicados = 2*(c*i + j) + 1, 2*(c*i + j) + 2
	//source = 0, sink = 2*r*c + 1
	int B, C, F;
	int Source = 0;
	for(int i = 0; i < r; ++i){
		for(int j = 0; j < c; ++j){
			cin >> grid[i][j];
			if(grid[i][j] == 'B'){
				B = c*i + j;
			}else if(grid[i][j] == 'C'){
				C = c*i + j;
			}else if(grid[i][j] == 'F'){
				F = c*i + j;
			}
		}
	}
	flowGraph<int> g(2*r*c + 1);
	//conectamos el source a B y a C
	g.addEdge(Source, out(B), 1, 0);
	g.addEdge(Source, out(C), 1, 0);
	//conectamos los nodos duplicados
	for(int i = 0; i < r; ++i){
		for(int j = 0; j < c; ++j){
			if(grid[i][j] == 'F'){
				g.addEdge(in(c*i + j), out(c*i + j), 2, 0);
			}else if(grid[i][j] == '.'){
				g.addEdge(in(c*i + j), out(c*i + j), 1, 0);
			}
		}
	}
	//conectamos las casillas entre si
	for(int i = 0; i < r; ++i){
		for(int j = 0; j < c; ++j){
			if(grid[i][j] == 'x') continue;
			for(auto mov : movs){
				int di, dj;
				tie(di, dj) = mov;
				int ni = i + di, nj = j + dj;
				if(0 <= ni && ni < r && 0 <= nj && nj < c && grid[ni][nj] != 'x' && grid[ni][nj] != 'B' && grid[ni][nj] != 'C'){
					g.addEdge(out(c*i + j), in(c*ni + nj), 1, 1);
				}
			}
		}
	}
	auto ans = g.maxFlowMinCost(Source, out(F));
	int flow = ans.first, cost = ans.second;
	if(flow == 2){
		cout << cost << "\n";
	}else{
		cout << "-1\n";
	}
	return 0;
}