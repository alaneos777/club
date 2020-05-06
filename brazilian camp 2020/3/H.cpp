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
using pii = pair<ll, ll>;
using vi = vector<int>;
 
ll a[11], b[11];
ll x, y;
vector<pii> res;
 
ll pot (ll b, int p ) {
    ll res = 1;
    while (p) {
        if (p & 1) res *= b;
        b *= b;
        p /= 2;
    }
    return res;
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    a[2] = 9;
    a[3] = 108;
    a[4] = 1107;
    a[5] = 11106;
    a[6] = 111105;
    a[7] = 1111104;
    a[8] = 11111103;
    a[9] = 111111102;
    
    b[1] = 111111111;
    b[2] = 11111112;
    b[3] = 1111113;
    b[4] = 111114;
    b[5] = 11115;
    b[6] = 1116;
    b[7] = 117;
    b[8] = 18;
    b[9] = 9;
    
    cin >> x >> y;
    
    while (x) {
        string s = to_string(x);
        
        if (s[0] == '1') {
            res.emplace_back(-1, 1);
            s = s.substr(1);
            if (s == "") s = "0";
            x = stoll(s);
        } else {
            ll inc = a[s[0] - '0'] * pot(10, s.size() - 1);
            res.emplace_back(1, inc / 9);
            x += inc;
        }
    }
    
    string t = to_string(y);
    reverse(all(t));
    for (int i = 0; i < t.size() && y; i++)
        if (t[i] != '0') {
            ll inc = b[t[i] - '0'] * pot(10, i);
            res.emplace_back(1, inc / 9);
            if (t[i] != '9') {
                res.emplace_back(-1, 9 - (t[i] - '0'));
            }
        }
    
    cout << "Stable" << endl;
    cout << res.size() << endl;
    for (auto r : res) {
        if (r.fi == 1) cout << "+ " << r.se << endl;
        else cout << "- " << r.se << endl;
    }
    
    return 0;
}
