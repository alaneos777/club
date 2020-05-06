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
using vll = vector<ll>;

const int MX = 1e5;
const ld eps = 1e-9;

const int g = 3, p = 998244353;

int nearest(int n){
    int ans = 1;
    while(ans < n) ans <<= 1;
    return ans;
}

ll power(ll a, ll n, ll m){
    ll ans = 1;
    if(m == p){
        n %= m-1;
        if(n < 0) n += m-1;
    }
    while(n){
        if(n & 1) ans = ans * a % m;
        n >>= 1;
        a = a * a % m;
    }
    return ans;
}

void ntt(vi & x, int inv){
    int n = x.size();
    for(int i = 1, j = 0; i < n-1; ++i){
        for(int k = n>>1; (j^=k) < k; k >>= 1);
        if(i < j) swap(x[i], x[j]);
    }
    vll wp(n>>1, 1);
    for(int k = 1; k < n; k <<= 1){
        ll wk = power(g, inv * (p-1) / (k<<1), p);
        for(int j = 1; j < k; ++j){
            wp[j] = wp[j-1] * wk % p;
        }
        for(int i = 0; i < n; i += k<<1){
            for(int j = 0; j < k; ++j){
                int u = x[i+j], v = x[i+j+k] * wp[j] % p;
                x[i+j] = u+v < p ? u+v : u+v-p;
                x[i+j+k] = u-v < 0 ? u-v+p : u-v;
            }
        }
    }
    if(inv == -1){
        ll nrev = power(n, p-2, p);
        for(int i = 0; i < n; ++i){
            x[i] = x[i] * nrev % p;
        }
    }
}

vi mult(vi a, vi b){
    assert(a.size() == b.size());
    int n = a.size();
    int sz = 2*n-1;
    int size = nearest(sz);
    a.resize(size), b.resize(size);
    ntt(a, 1), ntt(b, 1);
    for(int i = 0; i < size; ++i){
        a[i] = ll(a[i]) * b[i] % p;
    }
    ntt(a, -1);
    for(int i = n; i < 2*n-1; ++i){
        a[i-n] += a[i];
        if(a[i-n] >= p) a[i-n] -= p;
    }
    a.resize(n);
    for(int i = 0; i < n; ++i){
        a[i] = a[i] & 1;
    }
    return a;
}

vi shift(const vi & A, int k){
    int n = A.size();
    vi B(n);
    ll T = power(2, k, n);
    for(int i = 0; i < n; ++i){
        B[(i * T) % n] ^= A[i];
    }
    return B;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    string a, b, s;
    cin >> a >> b >> s;
    reverse(s.begin(), s.end());
    int n = a.size();
    vi A(n), B(n);
    forn(i, n){
        A[i] = a[n-1-i]-'0';
        B[i] = b[i]-'0';
    }
    vi ans(n); ans[0] = 1;
    for(int i = 0; i < s.size(); ++i){
        if(s[i] == '1') ans = mult(ans, shift(B, i));
    }
    ans = mult(ans, A);
    forn(i, n){
        cout << ans[n-1-i];
    }
    cout << "\n";
    return 0;
}
 