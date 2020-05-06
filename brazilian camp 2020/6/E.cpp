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

const int MX = 310;
const ld eps = 1e-9;

struct node {
    int x, y, z;
    bool operator < (const node &ot) const {
        if (x != ot.x) return x < ot.x;
        if (y != ot.y) return y < ot.y;
        return z < ot.z;
    }
};

bool ex[MX][MX][MX];
int dis[MX][MX][MX];
int n, a[MX], b[MX], c[MX], d[MX], z[MX];
vi cx, cy, cz;
vector<node> q[1000000];

void domap (vi &v) {
    sort(all(v));
    v.erase(unique(all(v)), v.end());
}

int find (vi &v, int x) {
    return lower_bound(all(v), x) - v.begin();
}

void mark (int a, int b, int c, int d, int z) {
    for (int i = a; i <= c; i++)
        for (int j = b; j <= d; j++)
            for (int k = 0; k <= z; k++)
                ex[i][j][k] = 1;
}

const int mod = MX;
int mx[] = {1, -1, 0, 0, 0, 0};
int my[] = {0, 0, 1, -1, 0, 0};
int mz[] = {0, 0, 0, 0, 1, -1};

bool valid (int x, int y, int z) {
    return 0 <= x && x < cx.size() 
        && 0 <= y && y < cy.size()
        && 0 <= z && z < cz.size()
        && !ex[x][y][z];
}

typedef pair<int, node> ii;

void dij (int ox, int oy, int oz) {
    memset(dis, -1, sizeof(dis));
    dis[ox][oy][oz] = 0;
    q[0].pb({ox, oy, oz});
    
    for (int ind = 0; ind < 1000000; ind++) {
        for (auto u : q[ind]) {
            int d = ind;
            int i = u.x;
            int j = u.y;
            int k = u.z;
            
            if (dis[i][j][k] < d) continue;
            
            for (int l = 0; l < 6; l++) {
                int x = i + mx[l];
                int y = j + my[l];
                int z = k + mz[l];
                
                if ((cx[x] & 1) || (cy[y] & 1) || (cz[z] & 1)) {
                    if (!valid(x, y, z)) continue;
                    x += mx[l];
                    y += my[l];
                    z += mz[l];
                }
                
                if (valid(x, y, z)) {
                    int w = abs(cx[i] - cx[x]) + abs(cy[j] - cy[y]) + abs(cz[k] - cz[z]);
                    if (dis[x][y][z] == -1 || d + w < dis[x][y][z]) {
                        dis[x][y][z] = d + w;
                        q[d + w].pb({x, y, z});
                    }
                }
            }
        }
        q[ind].clear();
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    int x1, x2, y1, y2, z1, z2;
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i] >> d[i] >> z[i];
        
        a[i] *= 2;
        b[i] *= 2;
        c[i] *= 2;
        d[i] *= 2;
        z[i] *= 2;
        
        cx.pb(a[i]), cx.pb(c[i]), cx.pb(a[i] + 1);
        cy.pb(b[i]), cy.pb(d[i]), cy.pb(b[i] + 1);
        cz.pb(0),    cz.pb(z[i]), cz.pb(1);
    }
    cin >> x1 >> y1 >> z1;
    x1 *= 2, y1 *= 2, z1 *= 2;
    cx.pb(x1), cy.pb(y1), cz.pb(z1);
    cin >> x2 >> y2 >> z2;
    x2 *= 2, y2 *= 2, z2 *= 2;
    cx.pb(x2), cy.pb(y2), cz.pb(z2);
    
    domap(cx);
    domap(cy);
    domap(cz);
    
    for (int i = 0; i < n; i++) {
        a[i] = find(cx, a[i]);
        b[i] = find(cy, b[i]);
        c[i] = find(cx, c[i]);
        d[i] = find(cy, d[i]);
        z[i] = find(cz, z[i]);
        
        mark(a[i]+1, b[i]+1, c[i]-1, d[i]-1, z[i]-1);
    }
    
    assert(cx.size() < MX);
    assert(cy.size() < MX);
    assert(cz.size() < MX);
    dij(find(cx, x1), find(cy, y1), find(cz, z1));
    cout << dis[find(cx, x2)][find(cy, y2)][find(cz, z2)] / 2 << endl;
    
    return 0;
}

