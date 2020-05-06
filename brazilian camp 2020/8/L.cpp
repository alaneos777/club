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

const int MX = 1e5;
const int MAXR = 15000;

vi inicio[MAXR + 2];
vector<ll> valor[MAXR + 2];

ll precio[MX + 2];

ll dp[MAXR + 2];
bool calc[MAXR + 2];

ll f(int r){
    if(r == 0) return 0;
    if(calc[r]) return dp[r];
    calc[r] = true;

    ll no_tomar = f(r - 1);
    ll res = no_tomar;

    int tam = inicio[r].size(), l;
    forn(i, tam){
        l = inicio[r][i];
        ll val = valor[r][i];

        ll tomar = f(l) + val;
        res = max(res, tomar);
    }

    dp[r] = res;
    return res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int m;
    cin >> m;
    int n;
    cin >> n;

    for(int t = 1; t <= m; t++) cin >> precio[t];

    for(int i = 1; i <= n; i++){
        int l, r;
        cin >> l >> r;
        int t;
        cin >> t;

        inicio[r].pb(l);
        valor[r].pb((r - l) * precio[t]);
    }

    cout << f(MAXR) << endl;
    
    return 0;
}

