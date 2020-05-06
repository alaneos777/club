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
using ll = long long;
using ld = long double;
 
const int MX = 1e5;
const ld eps = 1e-9;
 
bool eq(ld a, ld b){return abs(a-b) < eps;}
bool le(ld a, ld b){return a-b<-eps;}
bool leq(ld a, ld b){return a-b<=eps;}
bool ge(ld a, ld b){return a-b>eps;}
 
struct point{
    ld x, y;
    point(): x(0), y(0){}
    point(ld x, ld y): x(x), y(y){}
    point operator+(const point & p) const{return point(x+p.x, y+p.y);}
    point operator-(const point & p) const{return point(x-p.x, y-p.y);}
    point operator*(const ld & k) const{return point(x*k, y*k);}
    point operator/(const ld & k) const{return point(x/k, y/k);}
    ld dot(const point & p) const{return x*p.x + y*p.y;}
    ld cross(const point & p) const{return x*p.y - y*p.x;}
    point unit() const{
        ld l = sqrtl(x*x + y*y);
        return point(x/l, y/l);
    }
    point perp() const{return point(-y, x);}
    bool operator<(const point & p) const{
        if(!eq(x, p.x)) return le(x, p.x);
        return le(y, p.y);
    }
};
 
vector<point> ch(vector<point> P){
    sort(P.begin(), P.end());
    int n = P.size();
    vector<point> L, U;
    for(int i = 0; i < n; ++i){
        while(L.size() >= 2 && leq((L[L.size()-2]-P[i]).cross(L[L.size()-1]-P[i]), 0)){
            L.pop_back();
        }
        L.push_back(P[i]);
    }
    for(int i = n-1; i >= 0; --i){
        while(U.size() >= 2 && leq((U[U.size()-2]-P[i]).cross(U[U.size()-1]-P[i]), 0)){
            U.pop_back();
        }
        U.push_back(P[i]);
    }
    L.pop_back();
    U.pop_back();
    L.insert(L.end(), U.begin(), U.end());
    return L;
}
 
ld dist(const point & a, const point & v, const point & p){
    return abs(v.cross(p-a));
}
 
point intersect(const point & a1, const point & v1, const point & a2, const point & v2){
    //tv1*v2 = (a2-a1)*v2
    ld t = (a2-a1).cross(v2) / v1.cross(v2);
    return a1 + v1*t;
}
 
vector<point> smallest(const vector<point> & P){
    int n = P.size();
    auto dot = [&](int a, int b){return (P[(a+1)%n]-P[a]).dot(P[(b+1)%n]-P[b]);};
    auto cross = [&](int a, int b){return (P[(a+1)%n]-P[a]).cross(P[(b+1)%n]-P[b]);};
    ld area = numeric_limits<ld>::max();
    vector<point> ans;
    for(int i = 0, j = 0, k = 0, m = 0; i < n; ++i){
        while(ge(dot(i, j), 0)) j = (j+1)%n;
        if(!i) k = j;
        while(ge(cross(i, k), 0)) k = (k+1)%n;
        if(!i) m = k;
        while(le(dot(i, m), 0)) m = (m+1)%n;
        point v = P[(i+1)%n] - P[i];
        v = v.unit();
        point u = v.perp();
        ld h = dist(P[i], v, P[k]);
        ld w = dist(P[j], u, P[m]);
        if(le(h*w, area)){
            area = h*w;
            point A = intersect(P[j], u, P[i], v);
            point B = intersect(P[i], v, P[m], u);
            point C = intersect(P[m], u, P[k], v);
            point D = intersect(P[j], u, P[k], v);
            ans = {A, B, C, D};
        }
    }
    return ans;
}