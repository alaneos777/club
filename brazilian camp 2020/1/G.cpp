#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
using namespace std;
 
using pii = pair<int, int>;
using vi = vector<int>;
using ll = long long;
using ld = long double;
 
const int MX = 1e5;
const ll mod = 1000000;
ll n;
ll x[MX], ind, res, s[MX], m;
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    m = 12ll * mod * mod;
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll h, _m, s;
        cin >> h >> _m >> s;
        x[i] = h * mod * mod + _m * mod + s; 
        res += m - x[i];
    }
    
    sort(x, x+n);
    for (int i = 0; i < n; i++) {
        s[i] = x[i];
        if (i) s[i] += s[i-1];
    }
    
    for (int i = 0; i < n; i++) {
        ll p = (n - 1) * x[i] + (n - 1 - i) * m - (s[n-1] - s[i]);
        if (i) p -= s[i-1];
        
        if (p < res) {
            res = p;
            ind = x[i];
        }
    }
    
    cout << res / (mod * mod) << " " << (res % (mod * mod)) / mod << " " << res % mod << endl;
    
    return 0;
}
