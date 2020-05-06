#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
#define all(v) v.begin(), v.end()
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
 
int n, k;
vi st;
int s[1005], t[1005], c[1005];
flowGraph<int> *g;
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> t[i] >> c[i];
        st.pb(s[i]);
        st.pb(s[i] + t[i]);
    }
    
    sort(all(st));
    st.erase(unique(all(st)), st.end());
    
    g = new flowGraph<int>(st.size() + 2 * n + 5);
    
    for (int i = 0; i < n; i++) {
        g->addEdge(2 * i, 2 * i + 1, 1, -c[i]);
        g->addEdge(2 * n + lower_bound(all(st), s[i]) - st.begin(), 2 * i, 1, 0);
        g->addEdge(2 * i + 1, 2 * n + lower_bound(all(st), s[i] + t[i]) - st.begin(), 1, 0);
    }
    
    for (int i = 0; i + 1 < st.size(); i++)
        g->addEdge(2 * n + i, 2 * n + i + 1, k, 0);
    
    int s = 2 * n + st.size();
    int t = s + 1;
    g->addEdge(s, 2 * n, k, 0);
    g->addEdge(2 * n + (int)st.size() - 1, t, k, 0);
    
    g->maxFlowMinCost(s, t);
    
    for (int i = 0; i < n; i++)
        for (flowEdge<int> *e : g->adjList[2 * i])
            if (e->dest == 2 * i + 1)
                cout << e->flow << " ";
    cout << endl;
    
    return 0;
}
