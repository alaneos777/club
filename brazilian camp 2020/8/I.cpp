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
int n;
ii a[MX];

bool esPos (int m) {
    int mx = 0;
    for (int i = 0; i < n; i++) {
        if (mx > a[i].se) return 0;
        mx = max(mx, a[i].fi);
        mx += m;
    }
    return 1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, l;
        cin >> x >> l;
        a[i] = {x, x + l};
    }
    sort(a, a + n);
    
    ll i = 0, j = 2e9 + 5, rep = 32;
    while (rep--) {
        ll m = (i + j + 1) / 2;
        if (esPos(m)) i = m;
        else j = m;
    }
    cout << i << endl;
    
    return 0;
}

