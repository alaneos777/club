#include <bits/stdc++.h>
using namespace std;
using lli = __int128;
using ld = long double;

struct point{
    ld x, y;
    point(): x(0), y(0) {}
    point(ld x, ld y): x(x), y(y) {}
    point operator+(const point & p) const{
        return point(x +  p.x, y + p.y);
    }
    point operator-(const point & p) const{
        return point(x - p.x, y - p.y);
    }
    point operator*(ld k) const{
        return point(x*k, y*k);
    }
    point operator/(ld k) const{
        return point(x/k, y/k);
    }
    ld len() const{
        return sqrtl(x*x + y*y);
    }
    point normalize() const{
        return point(x / len(), y / len());
    }
    point perp() const{
        return point(-y, x);
    }
    bool operator==(const point & p) const{
        return x==p.x && y==p.y;
    }
};

istream&operator>>(istream & is, point & p){
    return is >> p.x >> p.y;
}

ostream&operator<<(ostream & os, const point & p){
    return os << "(" << p.x << ", " << p.y << ")";
}

const ld eps = 1e-9;

bool le(ld a, ld b){
    return a-b < -eps;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while(t--){
        point F1, F2; ld Dist;
        cin >> F1 >> F2 >> Dist;
        ld a = Dist/2;
        point C = (F1 + F2) / 2;
        ld c = (F1 - F2).len() / 2;
        ld b = sqrtl(a*a - c*c);
        point u1 = (F1 - F2).normalize();
        point u2 = u1.perp();
        if(F1 == F2){
            u1 = point(1, 0);
            u2 = point(0, 1);
        }
        ld t1 = atan2l(b*u2.y, a*u1.y);
        ld t2 = atan2l(b*u2.x, a*u1.x);
        point down = C - u1*a*cosl(t1) - u2*b*sinl(t1);
        point up = C + u1*a*cosl(t1) + u2*b*sinl(t1);
        point left = C - u1*a*cosl(t2) - u2*b*sinl(t2);
        point right = C + u1*a*cosl(t2) + u2*b*sinl(t2);
        lli D = down.y, U = up.y;
        if(D > U) swap(D, U);
        lli L = left.x, R = right.x;
        if(L > R) swap(L, R);
        int ans = 0;
        for(lli x = L-5; x <= R+5; ++x){
            for(lli y = D-5; y <= U+5; ++y){
                point P(x, y);
                if(le((P - F1).len() + (P - F2).len(), Dist)){
                    ans++;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}