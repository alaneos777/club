#include <bits/stdc++.h>
using namespace std;

double eps = 1e-8;

struct point{
	double x, y;
	point(): x(0), y(0) {}
	point(double x, double y): x(x), y(y) {}
	void read(){cin >> x >> y;}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	bool operator<(const point & p) const{
		if(abs(x - p.x) < eps){
			return y < p.y;
		}else{
			return x < p.x;
		}
	}
	double length() const{
		return hypot(x, y);
	}
};

bool comp1(const point & a, const point & b){
	return a.y < b.y;
}
double closestPairOfPoints(vector<point> & points){
	sort(points.begin(), points.end(), comp1);
	set<point> S;
	double ans = 1e9;
	point q;
	int pos = 0;
	for(int i = 0; i < points.size(); ++i){
		while(pos < i && abs(points[i].y - points[pos].y) >= ans){
			S.erase(points[pos++]);
		}
		auto lower = S.lower_bound({points[i].x - ans - eps, -1e9});
		auto upper = S.upper_bound({points[i].x + ans + eps, -1e9});
		for(auto it = lower; it != upper; ++it){
			double d = (points[i] - *it).length();
			if(d < ans){
				ans = d;
				q = *it;
			}
		}
		S.insert(points[i]);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	while(cin >> n && n != 0){
		vector<point> points(n);
		for(int i = 0; i < n; ++i){
			points[i].read();
		}
		double ans = closestPairOfPoints(points);
		if(ans < 10000){
			cout << fixed << setprecision(4) << ans << "\n";
		}else{
			cout << "INFINITY\n";
		}
	}
	return 0;
}