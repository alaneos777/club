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
using ii = pair<int, int>;
using vi = vector<int>;

const int MX = 100005;

int n, root;
ll d[MX], res, sz[MX], s[MX];
vector<ii> adj[MX];

void find (int u, int p = -1) {
    if (adj[u].size() == 1) {
        sz[u] = 1;
        s[u] = d[u];
        res -= d[u] * d[u];
        return;
    }
    
    for (ii &v : adj[u])
        if (v.fi != p) {
            d[v.fi] = d[u] + v.se;
            find(v.fi, u);
            sz[u] += sz[v.fi];
            s[u] += s[v.fi];
        }
}

void dfs (int u, int p = -1) {
    if (adj[u].size() == 1) {
        res += (sz[root] - 1) * d[u] * d[u];
        return;
    }
    
    for (ii &v : adj[u])
        if (v.fi != p) {
            dfs(v.fi, u);
            
            res += 2 * sz[v.fi] * (sz[u] - sz[v.fi]) * d[u] * d[u];
            res -= 4 * (sz[u] - sz[v.fi]) * s[v.fi] * d[u];
        }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }
    
    for (int i = 1; i <= n; i++)
        if (adj[i].size() > 1) {
            root = i;
            break;
        }
    
    find(root);
    dfs(root);
    res += s[root] * s[root];
    cout << res << endl;
    
    return 0;
}

