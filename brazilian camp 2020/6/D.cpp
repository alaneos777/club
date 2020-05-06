#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
#define all(v) v.begin(), v.end()
using namespace std;

using ll = long long int;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

int n;
map<int, int> mx, my;
vi a, b;

int near(int n){
    int ans = 1;
    while(ans < n) ans <<= 1;
    return ans;
}

ll powerMod(ll b, ll e, ll m){
    ll ans = 1;
    e %= m-1;
    if(e<0) e += m-1;
    while(e){
        if(e&1) ans = ans * b % m;
        e >>= 1;
        b = b*b % m;
    }
    return ans;
}

template<int prime, int gen>
void ntt(vi & x, int inv){
    int n = x.size();
    for(int i = 1, j = 0; i < n-1; ++i){
        for(int k = n>>1; (j^=k) < k; k>>=1);
        if(i<j) swap(x[i], x[j]);
    }
    vector<ll> wp(n>>1, 1);
    for(int k = 1; k < n; k<<=1){
        ll wk = powerMod(gen, inv * (prime-1)/(k<<1), prime);
        for(int j = 1; j < k; ++j)
            wp[j] = wp[j-1] * wk % prime;
        for(int i = 0; i < n; i += k<<1){
            for(int j = 0; j < k; ++j){
                int u = x[i+j], v = x[i+j+k] * wp[j] % prime;
                x[i+j] = u+v < prime ? u+v : u+v-prime;
                x[i+j+k] = u-v<0 ? u-v+prime : u-v;
            }
        }
    }
    if(inv == -1){
        ll nrev = powerMod(n, prime-2, prime);
        for(int i = 0; i < n; ++i)
            x[i] = x[i] * nrev % prime;
    }
}

const int p = 998244353, g = 3;

vi mul(vi & a, vi & b){
    int sz = a.size() + b.size() - 1;
    int SZ = near(sz);
    a.resize(SZ), b.resize(SZ);
    ntt<p, g>(a, 1), ntt<p, g>(b, 1);
    for(int i = 0; i < SZ; ++i)
        a[i] = (ll)a[i] * b[i] % p;
    ntt<p, g>(a, -1);
    a.resize(sz);
    return a;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        mx[x]++;
        my[y]++;
    }
    
    int sa = 0, sb = 0;
    
    a.resize(n + 1);
    b.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        sa = sa + mx[i];
        sb = sb + my[i];
        
        a[sa] = 1;
        b[sb] = 1;
    }
    
    vi res = mul(a, b);
    int cn = 0;
    for (int i = 0; i < res.size(); i++){
        cn += bool(res[i]);
    }
    cout << cn << endl;
    
    return 0;
}

