#include <bits/stdc++.h>
using namespace std;
using ld = long double;

struct point{
	ld x, y;
	point(){}
	point(ld x, ld y): x(x), y(y){}
	point operator+(const point& p) const{return point(x + p.x, y + p.y);}
	point operator-(const point& p) const{return point(x - p.x, y - p.y);}
	ld dot(const point& p) const{return x*p.x + y*p.y;}
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
		ld a = (B+C-A-D).dot(B+C-A-D), b = (A-C).dot(B+C-A-D), c = (A-C).dot(A-C);
		ld ans = 0;
		if(a > 0 && 0 <= -b && -b <= a){
			ans = c - b*b/a;
		}else{
			ans = min(c, a+2*b+c);
		}
		ans = sqrtl(ans);
		cout << "Case " << caso << ": " << fixed << setprecision(8) << ans << "\n";
	}
	return 0;
}