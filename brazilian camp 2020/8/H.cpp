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

const int MX = 2005;
int n, m, c1, c2, p[MX], t, res;
ii a[MX], b[MX];
vi pos[MX], neg[MX], cx, cy;
int pre[4 * MX], suf[4 * MX], mx[4 * MX], s[4 * MX];

void build (int i, int j, int pos) {
    if (i == j) {
        p[i] = pos;
        return;
    }
    int m = (i + j) / 2;
    build(i, m, pos * 2);
    build(m + 1, j, pos * 2 + 1);
}

int find (vi &v, int x) {
    return lower_bound(all(v), x) - v.begin() + 1;
}

void update (int x, int k) {
    int pos = p[x];
    
    mx[pos] = max(0, k);
    suf[pos] = max(0, k);
    pre[pos] = max(0, k);
    s[pos] = k;
    
    pos /= 2;
    while (pos) {
        mx[pos] = max({mx[pos * 2], mx[pos * 2 + 1], suf[pos * 2] + pre[pos * 2 + 1]});
        suf[pos] = max(suf[pos * 2 + 1], s[pos * 2 + 1] + suf[pos * 2]);
        pre[pos] = max(pre[pos * 2], s[pos * 2] + pre[pos * 2 + 1]);
        s[pos] = s[pos * 2] + s[pos * 2 + 1];
        
        pos /= 2;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].fi >> a[i].se;
        cx.pb(a[i].fi);
        cy.pb(a[i].se);
    }
    
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> b[i].fi >> b[i].se;
        cx.pb(b[i].fi);
        cy.pb(b[i].se);
    }
    
    sort(all(cx));
    cx.erase(unique(all(cx)), cx.end());
    
    sort(all(cy));
    cy.erase(unique(all(cy)), cy.end());

    for (int i = 0; i < n; i++) {
        a[i].fi = find(cx, a[i].fi);
        a[i].se = find(cy, a[i].se);
        pos[a[i].fi].pb(a[i].se);
    }
    
    cin >> c1 >> c2;
    for (int i = 0; i < m; i++) {
        b[i].fi = find(cx, b[i].fi);
        b[i].se = find(cy, b[i].se);
        neg[b[i].fi].pb(b[i].se);
    }
    
    t = cy.size();
    build(1, t, 1);
    
    for (int i = 1; i <= cx.size(); i++) {
        if (pos[i].empty()) continue;
        
        memset(mx, 0, sizeof(mx));
        memset(pre, 0, sizeof(pre));
        memset(suf, 0, sizeof(suf));
        memset(s, 0, sizeof(s));
        
        for (int k = i; k <= cx.size(); k++) {
            for (int j : pos[k])
                update(j, c1);
            
            for (int j : neg[k])
                update(j, -c2);

            res = max(res, mx[1]);
        }
    }
    
    cout << res << endl;
    
    return 0;
}

