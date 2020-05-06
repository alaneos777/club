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
 
const int MX = 3 * 1e4;
 
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
 
int nodo_in[MX + 2];
int nodo_out[MX + 2];
 
int nodo_real[10 * MX + 2];
 
flowGraph<int> *G;
 
vi aux_camino;
 
vi camino_pt1;
vi camino_pt2;
 
vi camino;
 
int a, b, c;
int s, t;
 
bool dfs(int nodo){
    if(nodo == t) return true;
 
    for(flowEdge<int> *v : G->adjList[nodo]){
        if(v->flow <= 0) continue;
 
        v->flow--;
 
        dfs(v->dest);
 
        int ori = nodo_real[nodo];
        if(nodo != s && nodo == nodo_out[ori]) aux_camino.pb(ori);
        return true;
    }
    return false;
}
 
void reconstruye(){
    dfs(nodo_in[c]);
    if(aux_camino[0] == a){
        camino_pt1 = aux_camino;
        camino_pt1.pop_back();
    }else{
        assert(aux_camino[0] == b);
        camino_pt2 = aux_camino;
        reverse(camino_pt2.begin(), camino_pt2.end());
    }
 
    aux_camino.clear();
    dfs(nodo_in[c]);
    if(aux_camino[0] == a){
        camino_pt1 = aux_camino;
        camino_pt1.pop_back();
    }else{
        assert(aux_camino[0] == b);
        camino_pt2 = aux_camino;
        reverse(camino_pt2.begin(), camino_pt2.end());
    }
 
    for(int nodo : camino_pt1) camino.pb(nodo);
    for(int nodo : camino_pt2) camino.pb(nodo);
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int n, m;
    cin >> n >> m;
 
    cin >> a >> b >> c;
    a--; b--; c--;
 
    int num_nodos = 0;
    forn(i, n){
        nodo_real[num_nodos] = i;
        nodo_in[i] = num_nodos++;
 
        nodo_real[num_nodos] = i;
        nodo_out[i] = num_nodos++;
    }
    nodo_real[num_nodos] = -1;
    s = num_nodos++;
    nodo_real[num_nodos] = -1;
    t = num_nodos++;
    
    G = new flowGraph<int>(num_nodos);
 
    forn(i, n){
        G->addEdge(nodo_in[i], nodo_out[i], 1 + (i == c), 0);
    }
 
    forn(i, m){
        int x, y, l;
        cin >> x >> y >> l;
        x--; y--;
 
        G->addEdge(nodo_out[x], nodo_in[y], 1, l);
        G->addEdge(nodo_out[y], nodo_in[x], 1, l);
    }
 
    G->addEdge(s, nodo_in[c], 2, 0);
    G->addEdge(nodo_out[a], t, 1, 0);
    G->addEdge(nodo_out[b], t, 1, 0);
 
    pair<int, int> res = G->maxFlowMinCost(s, t);
 
    if(res.fi < 2){
        cout << -1 << endl;
        return 0;
    }
 
    reconstruye();
    cout << camino.size() - 1 << " " << res.se << endl;
    for(int nodo : camino) cout << nodo + 1 << " ";
    cout << endl;
 
    return 0;
}
