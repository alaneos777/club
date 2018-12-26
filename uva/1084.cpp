#include <bits/stdc++.h>
using namespace std;

struct point{
	int x, y;

	point(): x(0), y(0){}
	point(int x, int y): x(x), y(y){}

	void read(){cin >> x >> y;}

	point operator-(const point & p) const{
		return point(x - p.x, y - p.y);
	}

	bool operator<(const point & p) const{
		if(x == p.x) return y < p.y;
		return x < p.x;
	}

	bool operator==(const point & p) const{
		return x==p.x && y==p.y;
	}

	int cross(const point & p) const{
		return x * p.y - y * p.x;
	}

	long double length() const{
		return hypotl(x, y);
	}
};

vector<point> convexHull(vector<point> P){
	sort(P.begin(), P.end());
	if(P.size() <= 2) return P;
	vector<point> L, U;
	for(int i = 0; i < P.size(); i++){
		while(L.size() >= 2 && (L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]) <= 0){
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	for(int i = P.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && (U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]) <= 0){
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}

double eps = 1e-9;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	long double pi = acosl(-1.0l);
	int caso = 1;
	while(cin >> n >> m && !(n == 0 && m == 0)){
		vector<point> points(n);
		for(int i = 0; i < n; ++i) points[i].read();
		vector<long double> perimeters(1 << n);
		for(int l = 1 << n, i = 1; i < l; ++i){
			perimeters[i] = numeric_limits<long double>::max();
			for(int j = (i-1)&i; j; j = (j-1)&i)
				perimeters[i] = min(perimeters[i], perimeters[j] + perimeters[i-j]);
			vector<point> in, out;
			for(int j = 0; j < n; ++j){
				if(i & (1 << j)) in.push_back(points[j]);
				else out.push_back(points[j]);
			}
			in = convexHull(in);
			long double p = 0;
			for(int i = 0; i < in.size(); ++i){
				p += (in[i] - in[(i+1)%in.size()]).length();
			}
			p += 2.0l*pi*m;
			perimeters[i] = min(perimeters[i], p);
		}
		cout << fixed << setprecision(2) << "Case " << caso++ << ": length = " << perimeters.back() << "\n";
	}
	return 0;
}