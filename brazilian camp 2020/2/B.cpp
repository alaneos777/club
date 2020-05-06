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
 
const int MX = 1000;
 
template<typename T>
struct flowEdge{
    int idx;
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
 
    void addEdge(int u, int v, int idx, T capacity, T cost = 0){
        flowEdge<T> *uv = new flowEdge<T>(v, 0, capacity, cost);
        flowEdge<T> *vu = new flowEdge<T>(u, 0, capacity, -cost);
 
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
 
        uv->idx = idx;
        vu->idx = -idx;
    }
 
    // INI Dinic
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
    // FIN Dinic
};
 
set<int> idx_cut;
bool visitado[MX + 2];
 
void dfs(const flowGraph<ll>& G, int nodo){
    if(visitado[nodo]) return;
    visitado[nodo] = true;
 
    for(flowEdge<ll> *v : G.adjList[nodo]){
        if(v->capacity == v->flow){
            // saturada
        }else{
            dfs(G, v->dest);
        }
    }
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int N, M;
    cin >> N >> M;
 
    flowGraph<ll> G(N);
    forn(i, M){
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
 
        G.addEdge(a, b, i + 1, c);
    }
 
    ll mf = G.dinic(0, N - 1);
 
    dfs(G, 0);
 
    for(int i = 0; i < N; i++){
        if(!visitado[i]) continue;
        for(flowEdge<ll> *v : G.adjList[i]){
            if(v->capacity > v->flow) continue;
            if(!visitado[v->dest]) idx_cut.insert(abs(v->idx));
        }
    }
 
    cout << idx_cut.size() << " " << mf << endl;
    set<int>::iterator it = idx_cut.begin();
    while(it != idx_cut.end()){
        cout << *it << " ";
        it++;
    }
    cout << endl;
 
    return 0;
}