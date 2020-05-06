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

const int MX = 200005;
int n, k, mem[MX][12], vis[MX][12];
ii p[MX];

int dp (int i, int k) {
    if (i == n || k < 0) return 0;
    
    int &res = mem[i][k];
    if (vis[i][k]) return res;
    vis[i][k] = 1;
    res = 0;
    
    if (k) {
        res = max(
            dp(i + 1, k),
            min(
                dp(i + 1, k - 1) - p[i].se,
                dp(i + 1, -1) + p[i].fi - p[i].se
            )
        );
    } else {
        res = max(
            dp(i + 1, k),
            dp(i + 1, k - 1) + p[i].fi - p[i].se
        );
    }
    
    return res;
}

void solve () {
    cin >> n >> k;
    
    for (int i = 0; i < n; i++)
        cin >> p[i].fi >> p[i].se;
    
    sort(p, p + n, [&] (ii a, ii b) {
        if (a.fi != b.fi) return a.fi < b.fi;
         return a.se > b.se;
    });
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= k; j++)
            vis[i][j] = 0;
    
    cout << dp(0, k) << endl;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    int t;
    cin >> t;
    while (t--)
        solve();
    
    return 0;
}

