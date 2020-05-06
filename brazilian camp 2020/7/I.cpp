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

const int MX = 255, SIG = 26, mod = 1000000021, mod2 = 1000000009;
int n, m;
char a[MX][MX], cn[MX][SIG];
ll b[SIG + 5], b2[SIG + 5], res;
vector<ll> v;
vi h, h2, odd, x;

ll add (int i, int c) {
    
    odd[i] -= cn[i][c] & 1;
    x[i] ^= cn[i][c];
    cn[i][c]++;
    odd[i] += cn[i][c] & 1;
    x[i] ^= cn[i][c];
    
    h[i] += b[c + 1];
    if (h[i] >= mod) h[i] -= mod;
    
    h2[i] += b2[c+1];
    if (h2[i] >= mod) h2[i] -= mod;
    
    return odd[i] <= 1 ? (h[i] ^ x[i] + 1ll * mod * h2[i]) : -i - 1;
}

int pal[2 * MX], t[2 * MX];
void manacher (vector<ll> &s) {
    int n = s.size(), m = (n << 1) - 1;
    
    for (int i = 0; i < m; i++)
        pal[i] = 0, t[i] = -1e9;
    
    for (int i = 0; i < n; i++)
        t[i << 1] = s[i];
    
    int x = 0;
    for (int i = 1; i < m; i++) {
        int &r = pal[i];
        
        if (i <= x + pal[x])
            r = min(pal[(x << 1) - i], x + pal[x] - i);
        
        while (i - r - 1 >= 0 && i + r + 1 < m && t[i - r - 1] == t[i + r + 1])
            r++;
        
        if (i + r >= x + pal[x])
            x = i;
    }
    
    for (int i = 0; i < m; i++)
        if (i - pal[i] == 0 || i + pal[i] == m - 1)
            pal[i]++;
        
    for (int i = 0; i < m; i++) {
        pal[i] = (pal[i] + 1) >> 1;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    srand(time(0));
    b[0] = 1;
    b[1] = (1ll * rand() * rand() + rand()) % mod;
    
    b2[0] = 1;
    b2[1] = (1ll * rand() * rand() + rand()) % mod;
    
    for (int i = 2; i < SIG + 5; i++) {
        b[i] = b[i-1] * b[1] % mod;
        b2[i] = b2[i-1] * b2[1] % mod2;
    }
    
    cin >> n >> m;
    
    v.resize(n);
    h.resize(n);
    h2.resize(n);
    odd.resize(n);
    x.resize(n);
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    
    for (int i = 0; i < m; i++) {
        memset(cn, 0, sizeof(cn));
        fill(all(h), 0);
        fill(all(h2), 0);
        fill(all(odd), 0);
        fill(all(x), 0);
        
        for (int j = i; j < m; j++) {
            
            for (int k = 0; k < n; k++) {
                v[k] = add(k, a[k][j] - 'a');
            }
            
            manacher(v);
            
            for (int k = 0; k < 2 * n - 1; k++) {
                if (k % 2 == 0) {
                    if (v[k / 2] >= 0)
                        res += pal[k];
                } else {
                    res += pal[k];
                }
            }
        }
    }
    
    cout << res << endl;
        
    return 0;
}

