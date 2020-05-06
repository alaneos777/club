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

int n;
string s, ts;

const int MX = 1000005;
int pal[2 * MX], t[2 * MX];

void manacher (string &s) {
    int n = s.size(), m = 2 * n - 1;
    
    for (int i = 0; i < m; i++)
        pal[i] = 0, t[i] = -1;
    
    for (int i = 0; i < n; i++)
        t[2 * i] = s[i];
    
    int x = 0;
    for (int i = 1; i < m; i++) {
        int &r = pal[i];
        
        if (i <= x + pal[x])
            r = min(pal[2 * x - i], x + pal[x] - i);
        
        while (i - r - 1 >= 0 && i + r + 1 < m && t[i - r - 1] == t[i + r + 1])
            r++;
        
        if (i + r >= x + pal[x])
            x = i;
    }
    
    for (int i = 0; i < m; i++)
        if (i - pal[i] == 0 || i + pal[i] == m - 1)
            pal[i]++;
    
    for (int i = 0; i < m; i++)
        pal[i] = (pal[i] + 1) / 2;
}

set<int> st;
int res = 0;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> ts;
    
    int i = 0, j = int(ts.size()) - 1;
    while (i < j) {
        s.pb(ts[i]);
        s.pb(ts[j]);
        i++, j--;
    }
    
    if (s.size()) {
        manacher(s);
        for (int i = 1; i < 2 * s.size() - 1; i += 2) {
            if (pal[i] == (i + 1) / 2) {
                res = max(res, pal[i]);
                st.insert(2 * pal[i]);
            }
        }
        
        for (int i = 1; i < 2 * s.size() - 1; i += 2) {
            int x = (i + 1) / 2 - pal[i];
            auto it = st.lower_bound(x);
            if (it == st.end() || *it >= (i + 1) / 2) continue;
            int y = (i + 1) / 2 - *it;
            res = max(res, (*it + 2 * y) / 2);
        }
    }
    
    cout << res << endl;
    
    return 0;
}

