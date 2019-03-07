#include <bits/stdc++.h>
using namespace std;

double eps = 1e-8, inf = numeric_limits<double>::max();
const double PI = acos(-1);

bool geq(double a, double b){return a-b >= -eps;}     //a >= b
bool leq(double a, double b){return b-a >= -eps;}     //a <= b
bool ge(double a, double b){return a-b > eps;}        //a > b
bool le(double a, double b){return b-a > eps;}        //a < b
bool eq(double a, double b){return abs(a-b) <= eps;}  //a == b
bool neq(double a, double b){return abs(a-b) > eps;}  //a != b

struct point{
	double x, y;
	point(): x(0), y(0) {}
	point(double x, double y): x(x), y(y) {}
	point operator+(const point & p) const{return point(x+p.x, y+p.y);}
	point operator-(const point & p) const{return point(x-p.x, y-p.y);}
	point operator*(const double & k) const{return point(x*k, y*k);}
	point operator/(const double & k) const{return point(x/k, y/k);}
	double length() const{return sqrt(x*x + y*y);}
	point normalize() const{return (*this)/this->length();}
	point rotate(const double & theta) const{return point(x*cos(theta) - y*sin(theta), x*sin(theta) + y*cos(theta));}
	double arg() const{double ang = atan2(y, x); if(ang < 0) ang += 2*PI; return ang;}
};

istream& operator>>(istream & is, point & p){
	cin >> p.x >> p.y;
	return is;
}

double mod(double x){
	while(le(x, 0)) x += 2*PI;
	while(geq(x, 2*PI)) x -= 2*PI;
	return x;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	point dest;
	double v, w;
	cin >> dest >> v >> w;
	double R = v / w;

	auto timeCCW = [&](double theta){
		point c(-R*sin(theta), R*cos(theta));
		double d = (dest - c).length();
		if(ge(R, d)) return inf;
		double phi = eq(R, d) ? 0 : acos(R / d);
		double alpha = (dest - c).arg();
		point exit = c + ((dest - c).normalize() * R).rotate(-phi);
		double t1 = theta / w;
		double t2 = mod(PI/2 + alpha - phi - theta) / w;
		double t3 = (dest - exit).length() / v;
		return t1 + t2 + t3;
	};

	auto timeCW = [&](double theta){
		point c(-R*sin(theta), -R*cos(theta));
		double d = (dest - c).length();
		if(ge(R, d)) return inf;
		double phi = eq(R, d) ? 0 : acos(R / d);
		double alpha = (dest - c).arg();
		point exit = c + ((dest - c).normalize() * R).rotate(phi);
		double t1 = theta / w;
		double t2 = mod(PI/2 - alpha - phi - theta) / w;
		double t3 = (dest - exit).length() / v;
		return t1 + t2 + t3;
	};

	auto solve = [&](function<double(double)> f, double l, double r){
		while(neq(l, r)){
			double first = l + (r - l) / 3;
			double second = l + 2 * (r - l) / 3;
			if(le(f(first), f(second))){
				r = second;
			}else{
				l = first;
			}
		}
		return f(r);
	};
	cout << fixed << setprecision(10) << min(solve(timeCCW, 0, dest.arg()), solve(timeCW, 0, mod(2*PI - dest.arg()))) << "\n";
	return 0;
}