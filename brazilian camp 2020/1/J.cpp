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
using ll = long long int;
using ld = long double;
 
const int MX = 1e5;
 
map<ll, int> factorize(ll m){
    map<ll, int> f;
    for(ll p = 2; p*p <= m; ++p){
        int pot = 0;
        while(m % p == 0){
            m /= p;
            pot++;
        }
        if(pot) f[p] = pot;
    }
    if(m > 1) f[m] = 1;
    return f;
}
 
ll pot(ll n, ll p){
    ll ans = 0, div = n;
    while(div /= p) ans += div;
    return ans;
}
 
ll power(ll a, ll b){
    ll ans = 1;
    while(b){
        if(b&1) ans = ans * a;
        b >>= 1;
        a = a * a;
    }
    return ans;
}
 
ll powerMod(ll a, ll b, ll m){
    ll ans = 1;
    while(b){
        if(b&1) ans = ans * a % m;
        b >>= 1;
        a = a * a % m;
    }
    return ans % m;
}
 
ll factmod(ll n, ll p, int s){
    ll ans = 1;
    ll ps = power(p, s);
    while(n > 1){
        ll q = n/ps, r = n%ps;
        ans = ans * (q%2==1 && !(p==2 && s>=3) ? ps-1 : 1) % ps;
        for(ll i = 2; i <= r; ++i){
            if(i%p == 0) continue;
            ans = ans * i % ps;
        }
        n /= p;
    }
    return ans;
}
 
ll inverse(ll a, ll m){
    ll r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
    while(r1){
        si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
        ri = r0 % r1, r0 = r1, r1 = ri;
    }
    if(s0 < 0) s0 += m;
    return s0;
}
 
ll crt(const vector<pair<ll, ll>> & system){
    ll prod = 1, p, ans = 0;
    for(auto par : system) prod *= par.second;
    for(auto par : system){
        ll ai, ni;
        tie(ai, ni) = par;
        p = prod / ni;
        ans = (ans + (ai % ni) * inverse(p, ni) % prod * p) % prod;
    }
    if(ans < 0) ans += prod;
    return ans;
}
 
/*
 * I love Tania <3
*/
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ll n, k, m;
    cin >> n >> k >> m;
    auto fact = factorize(m);
    vector<pair<ll, ll>> system;
    for(auto par : fact){
        ll p; int a;
        tie(p, a) = par;
        ll pa = power(p, a);
        ll qn = factmod(n, p, a), rn = pot(n, p);
        ll qk = factmod(k, p, a), rk = pot(k, p);
        ll qs = factmod(n-k, p, a), rs = pot(n-k, p);
        ll cong = qn * inverse(qk, pa) % pa * inverse(qs, pa) % pa * powerMod(p, rn-rk-rs, pa) % pa;
        system.emplace_back(cong, pa);
    }
    cout << crt(system) << "\n";
    return 0;
}