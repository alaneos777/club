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
 
const int MX = 1e5;
const ld eps = 1e-9;
 
bool eq(ld a, ld b){return abs(a-b) < eps;}
bool leq(ld a, ld b){return a-b<=eps;}
bool geq(ld a, ld b){return a-b>=-eps;}
 
struct point{
    ld x, y;
    point(): x(0), y(0){}
    point(ld x, ld y): x(x), y(y){}
    point operator+(const point & p) const{return point(x+p.x, y+p.y);}
    point operator-(const point & p) const{return point(x-p.x, y-p.y);}
    point operator*(const ld & k) const{return point(x*k, y*k);}
    ld dot(const point & p) const{return x*p.x + y*p.y;}
    ld cross(const point & p) const{return x*p.y - y*p.x;}
};
 
istream&operator>>(istream & is, point & p){
    return is >> p.x >> p.y;
}
 
ostream&operator<<(ostream & os, point & p){
    return os << "(" <<  p.x << ", " << p.y << ")";
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--){
        point a1, a2, b1, b2, v;
        cin >> a1 >> a2 >> b1 >> b2 >> v;
        ld A = (a1-a2).cross(v);
        ld B = (b2-b1).cross(v);
        ld C = (b1-a1).cross(v);
        vector<point> posible;
        bool ok = false;
        //cout << A << " " << B << " " << C << "\n";
        if(eq(A, 0) && eq(B, 0)){
            if(eq(C, 0)){
                posible.emplace_back(0, 0);
            }else{
                ok = false;
            }
        }else if(eq(A, 0)){
            ld x = 0, y = -C/B;
            if(geq(y, 0) && leq(y, 1)){
                posible.emplace_back(x, y);
            }
        }else if(eq(B, 0)){
            ld x = -C/A, y = 0;
            if(geq(x, 0) && leq(x, 1)){
                posible.emplace_back(x, y);
            }
        }else{
            ld x = -C/A, y = 0;
            if(geq(x, 0) && leq(x, 1)){
                posible.emplace_back(x, y);
            }
            x = -(B+C)/A, y = 1;
            if(geq(x, 0) && leq(x, 1)){
                posible.emplace_back(x, y);
            }
            x = 0, y = -C/B;
            if(geq(y, 0) && leq(y, 1)){
                posible.emplace_back(x, y);
            }
            x = 1, y = -(A+C)/B;
            if(geq(y, 0) && leq(y, 1)){
                posible.emplace_back(x, y);
            }
        }
        for(point p : posible){
            point a = a1 + (a2-a1)*p.x;
            point b = b1 + (b2-b1)*p.y;
            //cout << a << " " << b<< "\n";
            if(geq((b-a).dot(v), 0)){
                ok = true;
            }
        }
        if(ok) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}