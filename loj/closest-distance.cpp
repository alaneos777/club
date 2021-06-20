#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-9;

struct point{
	ld x, y;
	point(){}
	point(ld x, ld y): x(x), y(y){}
	point operator+(const point& p) const{return point(x + p.x, y + p.y);}
	point operator-(const point& p) const{return point(x - p.x, y - p.y);}
	point operator*(ld k) const{return point(x*k, y*k);}
	ld len() const{return sqrtl(x*x + y*y);}
};

istream& operator>>(istream& is, point& p){
	return is >> p.x >> p.y;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		point A, B, C, D;
		cin >> A >> B >> C >> D;
		auto dist = [&](ld t){
			point p1 = A + (B-A)*t;
			point p2 = C + (D-C)*t;
			return (p1 - p2).len();
		};
		ld L = 0, R = 1;
		while(abs(L-R) >= eps){
			ld m1 = L + (R-L)/3;
			ld m2 = R - (R-L)/3;
			if(dist(m1) < dist(m2)){
				R = m2;
			}else{
				L = m1;
			}
		}
		ld t = (L+R)/2;
		ld ans = dist(t);
		cout << "Case " << caso << ": " << fixed << setprecision(8) << ans << "\n";
	}
	return 0;
}