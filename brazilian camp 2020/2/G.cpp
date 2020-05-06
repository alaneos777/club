#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
using namespace std;
 
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;
 
template<typename T>
struct flowEdge{
    int dest;
    T flow, capacity, cost;
    flowEdge *res;
 
    flowEdge(): dest(0), flow(0), capacity(0), cost(0), res(NULL) {}
    flowEdge(int dest, T flow, T capacity, T cost = 0):
        dest(dest), flow(flow), capacity(capacity), cost(cost), res(NULL) {}
 
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
                    if(v->capacity > v->flow && distance[v->dest] > 
                        distance[u] + v->cost){
                        
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
 
    int N, M;
    cin >> N >> M;
    
    flowGraph<ll> G(N);
 
    forn(i, M){
        int a, b;
        cin >> a >> b;
        a--; b--;
 
        int cap, cost;
        cin >> cap >> cost;
 
        G.addEdge(a, b, cap, cost);
    }
 
    pair<ll, ll> res = G.maxFlowMinCost(0, N - 1);
 
    cout << res.se << endl;
 
    return 0;
}