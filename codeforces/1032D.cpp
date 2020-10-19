#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

struct point{
	ld x, y;
	point(): x(0), y(0) {}
	point(ld x, ld y): x(x), y(y) {}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	ld len1() const{return abs(x) + abs(y);}
	ld len() const{return hypotl(x, y);}
};

int main(){
	ld a, b, c;
	cin >> a >> b >> c;
	//line ax+by+c=0
	point A, B;
	cin >> A.x >> A.y >> B.x >> B.y;
	ld ans = (A - B).len1();
	/*
	line x=A.x:
	y = -(c+a*A.x)/b
	*/
	/*
	line y=A.y:
	x = -(c+b*A.y)/a
	*/
	vector<point> lhs, rhs;
	if(b != 0){
		lhs.emplace_back(A.x, -(c + a*A.x) / b);
		rhs.emplace_back(B.x, -(c + a*B.x) / b);
	}
	if(a != 0){
		lhs.emplace_back(-(c + b*A.y) / a, A.y);
		rhs.emplace_back(-(c + b*B.y) / a, B.y);
	}
	for(point izq : lhs){
		for(point der : rhs){
			ans = min(ans, (A - izq).len1() + (izq - der).len() + (B - der).len1());
		}
	}
	cout << fixed << setprecision(9) << ans << "\n";
	return 0;
}