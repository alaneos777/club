#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define fi first
#define se second
using namespace std;
 
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;
 
struct tupla {
    int a, b, c, n;
    void impr () {
        cout << a << " " << b << " " << c << " " << n << endl;
    }
};
 
#define n3(n) (1ll*(n)*(n)*(n))
#define n2(n) (1ll*(n)*(n))
 
tupla f (ll n) {
    tupla res;
    ll mx = 3;
    while (n3(mx) * (mx - 2) < n)
        mx++;
    
    // Encuentra a
    int f = 1;
    ll tot = n3(mx - 1) * (mx - 3);
    for (int i = 1; i <= mx; i++) {
        if (tot + n2(mx) * (mx - 2) - f * n2(mx - 1) * (mx - 3) < n && i < mx) {
            tot += n2(mx) * (mx - 2) - f * n2(mx - 1) * (mx - 3);
        } else {
            res.a = i;
            f &= i != mx;
            break;
        }
    }
    
    // Encuentra b
    for (int i = 1; i <= mx; i++) {
        if (tot + mx * (mx - 2) - f * (mx - 1) * (mx - 3) < n && i < mx) {
            tot += mx * (mx - 2) - f * (mx - 1) * (mx - 3);
        } else {
            res.b = i;
            f &= i != mx;
            break;
        }
    }
    
    // Encuentra c
    for (int i = 1; i <= mx; i++) {
        if (tot + (mx - 2) - f * (mx - 3) < n && i < mx) {
            tot += (mx - 2) - f * (mx - 3);
        } else {
            res.c = i;
            f &= i != mx;
            break;
        }
    }
    
    // Encuentra n
    if (!f) {
        res.n = n - tot + 2;
    } else {
        res.n = mx;
    }
    
    return res;
}
 
ll l, r;
const ld eps = 1e-12;
 
string great(ld a, ld b, ld c, ld n){
    if(c == 1) return ">";
    if(a > b) swap(a, b);
    ld lhs = log1pl(powl(b/a, n)) / logl(c) + n * (log2l(a) / log2l(c));
    ld rhs = n;
    if(lhs-rhs > -eps) return ">";
    else return "<";
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    cin >> l >> r;
    
    for (ll i = l; i <= r; i++) {
        auto t = f(i);
        //f(i).impr();
        cout << t.a << "^" << t.n << "+" << t.b << "^" << t.n << great(t.a, t.b, t.c, t.n) << t.c << "^" << t.n << "\n";
    }
    
    return 0;
}
