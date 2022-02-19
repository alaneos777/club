// You told me...
// At your absolute best, you still won't be good enough for the wrong person... 
// At your worst, you'll still be worth it to the right person...
 
// ............................................................................................
// It was good while it lasted, good bye...                                                   .
// I believe I really loved you... to that point that I always want to hear your voice...     .
// But before my hand could reach you... you seem to be slowly disappearing from my sight...  .
// ............................................................................................
 
#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
 
#define pb push_back
#define ff  first
#define ss second
#define tm1 first
#define tm2 second.first
#define tm3 second.second
#define sz(x) ll(x.size())
#define fill(x, v) memset(x, v, sizeof(x))
#define all(v) (v).begin(), (v).end()
#define FER(i,a,b) for(ll i=ll(a); i< ll(b); ++i)
#define IFR(i,a,b) for(ll i=ll(a); i>=ll(b); --i )
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
 
#define N 100002
#define mod1 1000000007
// #define mod1 998244353
#define mod2 1000000009
#define bas 987625403
#define sqr(x) (x)*(x)  
#define INF (ll)1e18
 
using namespace std;
using namespace __gnu_pbds;
 
 
typedef long long ll;
typedef pair<ll, ll> ii;
typedef pair<ll, ii > tri;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef tree<ii, null_type, less<ii>, rb_tree_tag, tree_order_statistics_node_update> S_t;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
struct custom_Hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
 
#define trace(...) fff(#__VA_ARGS__, __VA_ARGS__)
template<typename t> void fff(const char* x, t&& val1) { cout<<x<< " : "<<val1<<"\n";}
template<typename t1, typename... t2> void fff(const char* x, t1&& val1, t2&&... val2){
    const char* xd=strchr(x+1, ',');
    cout.write(x, xd-x)<<" : "<<val1<<" | ";
    fff(xd+1, val2...);
}
 
 
inline ll add(ll a, ll b, ll mod) { return a+b < mod? a+b : a+b-mod;}
inline ll rem(ll a, ll b, ll mod) { return a >= b? a - b: a- b + mod;}
inline ll mul(ll a, ll b, ll mod) { return (long long) a*b%mod;}
inline void Mul(ll &a, ll b, ll mod) { a = (long long) a*b%mod;}
inline ll bp(ll a, ll p, ll mod){
    ll ret;
    for(ret = 1; p; p>>=1, Mul(a, a, mod)) (p & 1) && (Mul(ret, a, mod), 1);
    return ret;
}
 
static inline void read(ll &result) {
    bool minus = false;
    char ch;
    ch = getchar();
    while (true) {
        if (ch == '-') break;
        if (ch >= '0' and ch <= '9') break;
        ch = getchar();
    }
    (ch == '-')? minus = true: result = ch-'0';
    while (true) {
        ch = getchar();
        if (ch < '0' or ch > '9') break;
        result = (result<<3)+ (result<<1) + (ch - '0');
    }
    if(minus) result = -result;
}
 

bool Q;
struct line{
    mutable ll k, m, p;
    bool operator<(const line &o) const{
        return Q? p<o.p: k<o.k;
    }
};
struct LineContainer:multiset<line>{
    inline ll div(ll a, ll b){
        return a/b -((a ^b ) < 0 and a%b);
    }
    inline bool isect(iterator x, iterator y){
        if(y == end()){x->p = INF; return false;}
        if(x->k==y->k) x->p = x->m > y->m? INF:-INF;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    inline void add(ll k, ll m){
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if(y != begin() and isect(--x, y)) isect(x, erase(y));
        while((y = x) != begin() and (--x)->p >= y->p) isect(x, erase(y));
    }
    inline ll query(ll x){
        assert(!empty());
        Q = 1; auto l = *lower_bound({0,0,x}); Q=0;
        return l.k*x + l.m;
    }
};


ll tsz[1<<20], ar[1<<20], br[1<<20], dp[1<<20];
vi adj[1<<20];
inline void dfs(ll u, ll pp, LineContainer &ch){
    tsz[u] = 1;
    for(auto xd: adj[u]) if(xd != pp){
        LineContainer cur;
        dfs(xd, u, cur);
        tsz[u] += tsz[xd];
        for(auto xd: cur) ch.add(xd.k, xd.m);
    }
    dp[u] -= tsz[u] == 1? 0: ch.query(ar[u]);
    ch.add(-br[u], -dp[u]);
}

int main(){
    fastio;
    ll n; cin >> n;
    FER(i, 0, n) cin >> ar[i];
    FER(i, 0, n) cin >> br[i];
    FER(i, 0, n - 1){
        ll a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    LineContainer ch;
    dfs(0, -1, ch);
    FER(i, 0, n) cout<<dp[i]<<"\n";
    return 0;
}