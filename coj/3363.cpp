#include <bits/stdc++.h>
using namespace std;

struct point{
	double x, y;
	point(){
		x = y = 0;
	}
	point(double x, double y){
		this->x = x, this->y = y;
	}
	point operator+(const point & b) const{
		return point(x + b.x, y + b.y);
	}
	point operator-(const point & b) const{
		return point(x - b.x, y - b.y);
	}
	point operator*(double k) const{
		return point(k * x, k * y);
	}
	point operator/(double k) const{
		return point(x / k, y / k);
	}
	double size() const{
		return hypot(x, y);
	}
	point rotate(){
		return point(-y, x);
	}
};

int main(){
	int t;
	double h;
	point a, b, c, u;
	scanf("%d", &t);
	while(t--){
		scanf("%lf %lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y, &h);
		u = b - a; u = u / u.size();
		c = (a + b) / 2.0 + u.rotate() * h;
		printf("%0.3lf %0.3lf\n", c.x, c.y);
	}
	return 0;
}