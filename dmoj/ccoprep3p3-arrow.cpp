#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const long double eps = 1e-21;
struct ld{
	long double x;
	ld(): x(0){}
	ld(long double x): x(x){}
	ld(long double x, long double y): x(x/y){}
	ld operator+(const ld& f) const{return ld(x + f.x);}
	ld operator-() const{return ld(-x);}
	ld operator-(const ld& f) const{return *this + (-f);}
	ld operator*(const ld& f) const{return ld(x * f.x);}
	ld operator/(const ld& f) const{return ld(x / f.x);}
	ld operator+=(const ld& f){*this = *this + f; return *this;}
	ld operator-=(const ld& f){*this = *this - f; return *this;}
	ld operator++(int xd){*this = *this + 1; return *this;}
	ld operator--(int xd){*this = *this - 1; return *this;}
	ld operator*=(const ld& f){*this = *this * f; return *this;}
	ld operator/=(const ld& f){*this = *this / f; return *this;}
	bool operator==(const ld& f) const{return abs(x - f.x) <= eps;}
	bool operator!=(const ld& f) const{return abs(x - f.x) > eps;}
	bool operator>(const ld& f) const{return x - f.x > eps;}
	bool operator<(const ld& f) const{return f.x - x > eps;}
	bool operator>=(const ld& f) const{return x - f.x >= -eps;}
	bool operator<=(const ld& f) const{return f.x - x >= -eps;}
};
istream& operator>>(istream& is, ld& f){return is >> f.x;}
ostream& operator<<(ostream& os, const ld& f){return os << f.x;}

const ld inf = 1e50;

struct point{
	ld x, y;
	point(){}
	point(ld x, ld y): x(x), y(y) {}

	point operator+(const point& p) const{return point(x + p.x, y + p.y);}
	point operator-(const point& p) const{return point(x - p.x, y - p.y);}
	point operator*(ld k) const{return point(x * k, y * k);}

	ld dot(const point& p) const{return x * p.x + y * p.y;}
	ld cross(const point& p) const{return x * p.y - y * p.x;}

	bool half(const point& p) const{
		return p.cross(*this) < 0 || (p.cross(*this) == 0 && p.dot(*this) < 0);
	}
};

struct plane{
	point a, v;
	plane(): a(), v(){}
	plane(const point& a, const point& v): a(a), v(v){}

	bool inside(const point& p) const{
		return v.cross(p - a) >= 0;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<plane> planes(2*n+2);
	planes[0] = {{0, 0}, {1, 0}};
	planes[1] = {{0, 0}, {0, -1}};
	for(int i = 0; i < n; ++i){
		int pos, lo, hi;
		cin >> pos >> lo >> hi;
		planes[2*i+2] = {{ld(hi, pos), 0}, {pos, 1}};
		planes[2*i+3] = {{ld(lo, pos), 0}, {-pos, -1}};
	}
	point p = planes[0].a;
	int ans = 0;
	bool empty = false;
	for(int i = 0; i < 2*n+2; ++i){
		if(empty) break;
		if(planes[i].inside(p)) continue;
		ld lo = -inf, hi = inf;
		for(int j = 0; j < i; ++j){
			ld A = planes[j].v.cross(planes[i].v);
			ld B = planes[j].v.cross(planes[j].a - planes[i].a);
			if(A > 0){
				lo = max(lo, B/A);
			}else if(A < 0){
				hi = min(hi, B/A);
			}else{
				if(B > 0){
					ans = i-1;
					empty = true;
					break;
				}
			}
			if(lo > hi){
				ans = i-1;
				empty = true;
				break;
			}
		}
		if(!empty) p = planes[i].a + planes[i].v*lo;
	}
	//cout << "(" << p.x << ", " << p.y << ")\n";
	if(!empty) ans = 2*n+1;
	ans = (ans + 1) / 2 - 1;
	cout << ans << "\n";
	return 0;
}