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
 
const int MX = 100005;
int n, m, k, c[MX], vis[MX], p[MX], sz[MX], istom[MX], f;
vi adj[MX], tom;
set<int> res;
 
void findC (int u) {
    vis[u] = 1;
    
    for (int v : adj[u])
        if (v != p[u]) {
            if (vis[v] && !c[v]) {
                
                int w = u;
                do {
                    c[w] = u;
                    sz[u]++;
                    if (w == v) break;
                    w = p[w];
                } while (1);
                
            } else if (!vis[v]) {
                p[v] = u;
                findC(v);
            }
        }
}
 
void allC (int u) {
    res.insert(u);
    vis[u] = 1;
    for (int v : adj[u])
        if (!vis[v])
            allC(v);
}
 
void gofor (int u) {
    vis[u] = 1;
    if (c[u] && sz[c[u]] >= k)
        f = 1;
    res.insert(u);
    
    for (int v : adj[u])
        if (!vis[v])
            gofor(v);
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    
    cin >> k;
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        tom.pb(x);
        istom[x] = 1;
    }
    
    findC(tom[0]);
    memset(vis, 0, sizeof(vis));
    
    if (!c[tom[0]] || sz[c[tom[0]]] < k) {
        for (int u : tom)
            vis[u] = 1;
    }
    
    gofor(tom[0]);
    memset(vis, 0, sizeof(vis));
    
    if (f) {
        allC(tom[0]);
        memset(vis, 0, sizeof(vis));
    }
    
    cout << res.size() << endl;
    for (int r : res)
        cout << r << " ";
    cout << endl;
    
    return 0;
}