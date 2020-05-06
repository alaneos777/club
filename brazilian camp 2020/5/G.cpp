#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i = 0; i < n; i++)
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define x first
#define y second
using namespace std;
 
using ll = long long;
using ld = long double;
using point = pair<ll, ll>;
using vi = vector<int>;
 
const int MX = 1e5;
const ld eps = 1e-9;
 
ld triangle(point a, point b){
    ll sign = b.x*a.y - b.y*a.x;
    if(sign == 0) return 0;
    if(sign < 0) swap(a, b);
    ld ans = 0;
    if(a.x < b.x){
        ll n = a.x;
        if(n%2 == 0) n--; //rojo
        ans = abs(ld(a.y)/ld(a.x) - ld(b.y)/ld(b.x)) * n*(n+1)/4;
        n = b.x - a.x;
        if(b.x%2 == 0){ //blanco
            if(n%2 == 1) ans += abs(ld(b.y)/ld(b.x)*ld(a.x) - ld(a.y)) * (n-1)/4;
            else ans += abs(ld(b.y)/ld(b.x)*ld(a.x) - ld(a.y)) * (n+1)/4;
        }else{ //rojo
            if(n%2 == 0) ans += abs(ld(b.y)/ld(b.x)*ld(a.x) - ld(a.y)) * (n-1)/4;
            else ans += abs(ld(b.y)/ld(b.x)*ld(a.x) - ld(a.y)) * (n+1)/4;
        }
    }else if(b.x < a.x){
        ll n = b.x;
        if(n%2 == 0) n--; //rojo
        ans = abs(ld(a.y)/ld(a.x) - ld(b.y)/ld(b.x)) * n*(n+1)/4;
        n = a.x - b.x;
        if(a.x%2 == 0){ //blanco
            if(n%2 == 1) ans += abs(ld(a.y)/ld(a.x)*ld(b.x) - ld(b.y)) * (n-1)/4;
            else ans += abs(ld(a.y)/ld(a.x)*ld(b.x) - ld(b.y)) * (n+1)/4;
        }else{ //rojo
            if(n%2 == 0) ans += abs(ld(a.y)/ld(a.x)*ld(b.x) - ld(b.y)) * (n-1)/4;
            else ans += abs(ld(a.y)/ld(a.x)*ld(b.x) - ld(b.y)) *(n+1)/4;
        }
    }else{
        ll n = a.x;
        if(n%2 == 0) ans = abs(ld(a.y) - ld(b.y)) * (n-1)/4;
        else ans = abs(ld(a.y) - ld(b.y)) * (n+1)/4;
    }
    return ans * (sign > 0 ? 1 : -1);
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<point> points(n);
    ll mini_x = 0, mini_y = 0;
    for(point & pt : points){
        cin >> pt.y >> pt.x;
        mini_x = min(mini_x, pt.x);
        mini_y = min(mini_y, pt.y);
    }
    mini_x = abs(mini_x) + 100;
    mini_y = abs(mini_y) + 100;
    if(mini_x % 2 == 1) mini_x++;
    forn(i, n){
        points[i].x += mini_x;
        points[i].y += mini_y;
    }
    ld ans = 0;
    forn(i, n){
        ld tmp = triangle(points[i], points[(i+1)%n]);
        ans += tmp;
    }
    ans = abs(ans);
    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}