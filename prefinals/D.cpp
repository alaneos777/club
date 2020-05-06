#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

struct point{
	ld x, y, z;
	ld norm() const{return x*x + y*y + z*z;}
	bool operator<(const point & p) const{return norm() < p.norm();}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<point> points(n);
	for(point & p : points){
		cin >> p.x >> p.y >> p.z;
	}
	sort(points.begin(), points.end());
	cout << fixed << setprecision(9) << sqrtl(points[k-1].norm()) << "\n";
	return 0;
}