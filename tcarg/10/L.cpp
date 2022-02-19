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
#define INF 1e18
 
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

vii adj[1<<20];
vi comp[1<<3], resp[1<<3];
ll vis[1<<20], T[1<<20], boc;

inline ll dfs(ll v, ll sw, ll type, ll color){
    ll ans = sw;
    if (sw == 1) comp[type].push_back(v);
    T[v] = sw;
    vis[v] = boc;
    for (auto [to, w] : adj[v]){
        auto cur = w ^ color ^ sw;
        if (vis[to] == boc and cur != T[to]) return (ll)INF;
        if (vis[to] == boc) continue;
        ans += dfs(to, cur, type, color);
    }
    return ans;
}
 
int main(){
	fastio;
    ll n, m; cin >> n >> m;
    FER(i, 0, m){
        ll a, b;
        char c; cin >> a >> b >> c; a--, b--;
        auto val = c == 'R'? 1 : 0;
        adj[a].pb({b, val});
        adj[b].pb({a, val});
    }    
    auto solve = [&](ll color){
        boc++;
        ll ans = 0, st = boc;
        FER(i, 0, n){
            if(vis[i] >= st) continue;
            FER(j, 0, 2) comp[j].clear();
            auto L = dfs(i, 0, 0, color); boc++;
            auto R = dfs(i, 1, 1, color); boc++;
            ans += min(R, L);
            if(ans >= INF) return (ll)INF;
            if(L < R) for(auto xd: comp[0]) resp[color].pb(xd);
            else for(auto xd: comp[1]) resp[color].pb(xd);
        }
        return ans;
    };
    auto L = solve(0), R = solve(1);
    auto SryGabe = min(L, R);
    if(SryGabe >= INF) return cout<<"-1\n", 0;
    if(L > R) swap(resp[0], resp[1]);
    cout<<SryGabe<<"\n";
    for(auto xd: resp[0]) cout<<xd + 1<<" "; cout<<"\n";
    return 0;
}