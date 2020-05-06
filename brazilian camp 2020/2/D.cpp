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
 
int n, k, v[1005][10], f[1005];
flowGraph<int> *g;
 
set<int> st;
int vis[1005];
 
bool dom (int i, int j) {
    int cn = 0;
    for (int l = 0; l < k; l++) {
        if (v[i][l] < v[j][l]) return 0;
        if (v[i][l] > v[j][l]) cn++;
    }
    return cn;
}
 
void dfs (int u) {
    if (vis[u]) return;
    vis[u] = 1;
    
    for (flowEdge<int> *e : g->adjList[u])
        if (e->flow < e->capacity)
            dfs(e->dest);
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++)
            cin >> v[i][j];
        cin >> f[i];
    }
    
    g = new flowGraph<int>(n + 5);
    for (int i = 1; i <= n; i++) {
        if (f[i] == 0) g->addEdge(0, i, 1);
        else g->addEdge(i, n + 1, 1);
        
        for (int j = 1; j <= n; j++)
            if (f[i] == 0 && f[j] == 1 && dom(i, j))
                g->addEdge(i, j, 2);
    }
    
    cout << g->dinic(0, n + 1) << endl;
    dfs(0);
 
    for (int i = 1; i <= n; i++)
        if ((f[i] == 0 && !vis[i]) || (f[i] == 1 && vis[i]))
            st.insert(i);
    
    for (int x : st)
        cout << x << " ";
    cout << endl;
    
    return 0;
}
