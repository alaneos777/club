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
        flowEdge<T> *vu = new flowEdge<T>(u, capacity, capacity, -cost);
 
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
        
        uv->idx = idx;
        vu->idx = idx;
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
 
const int inf = 1e9;
int n, m, s, t;
char a[55][55];
 
bool valid (int i, int j) {
    return 1 <= i && i <= n && 1 <= j && j <= m;
}
 
int num (int i, int j) {
    return i * (m + 1) + j;
}
 
flowGraph<int> *g;
 
int mx[] = {1, -1, 0, 0};
int my[] = {0, 0, 1, -1};
 
int vis[100000];
void dfs (int u) {
    if (vis[u]) return;
    vis[u] = 1;
    
    for (flowEdge<int> *e : g->adjList[u])
        if (e->flow < e->capacity)
            dfs(e->dest);
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    g = new flowGraph<int>(2 * (n + 1) * (m + 1) + 5);
        
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == 'A') {
                s = num(i, j);
                g->addEdge(2 * num(i, j), 2 * num(i, j) + 1, num(i, j), inf);
            } else if (a[i][j] == 'B') {
                t = num(i, j);
                g->addEdge(2 * num(i, j), 2 * num(i, j) + 1, num(i, j), inf);
            } else if (a[i][j] == '#') {
                //g.addEdge(2 * num(i, j), 2 * num(i, j) + 1, num(i, j), 0);
            } else if (a[i][j] == '-') {
                g->addEdge(2 * num(i, j), 2 * num(i, j) + 1, num(i, j), inf);
            } else {
                g->addEdge(2 * num(i, j), 2 * num(i, j) + 1, num(i, j), 1);
            }
            
            for (int k = 0; k < 4; k++) {
                int x = i + mx[k];
                int y = j + my[k];
                if (valid(x, y))
                    g->addEdge(2 * num(i, j) + 1, 2 * num(x, y), -1, inf);
            }
        }
    
    int res = g->dinic(2 * s, 2 * t + 1);
    if (res > n * m) {
        cout << -1 << endl;
        return 0;
    }
    
    dfs(2 * s);
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j] == '.' && vis[2 * num(i, j)] != vis[2 * num(i, j) + 1])
                a[i][j] = '+';
    
    cout << res << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            cout << a[i][j];
        cout << endl;
    }
    
    return 0;
}