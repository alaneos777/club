#include <bits/stdc++.h>
using namespace std;

struct point{
	double x, y, z;
	point(): x(0), y(0), z(0){}
	point(double x, double y, double z): x(x), y(y), z(z){}
	void read(){cin >> x >> y >> z;}
	point cross(const point & p) const{
		return point(y * p.z - z * p.y, -x * p.z + z * p.x, x * p.y - y * p.x);
	}
	double length(){
		return hypot(hypot(x, y), z);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	point A, B;
	A.read(), B.read();
	cout << fixed << setprecision(4) << A.cross(B).length() / 12.0 << "\n";
	return 0;
}