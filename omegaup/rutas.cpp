#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct point{
	lli x, y;
	int idx;

	point(){
		x = y = 0;
	}
	point(lli x, lli y){
		this->x = x, this->y = y;
	}

	point operator+(const point & p) const{
		return point(x + p.x, y + p.y);
	}
	point operator-(const point & p) const{
		return point(x - p.x, y - p.y);
	}

	lli dot(const point & p) const{
		return x * p.x + y * p.y;
	}
	lli cross(const point & p) const{
		return x * p.y - y * p.x;
	}

	bool operator==(const point & p) const{
		return x == p.x && y == p.y;
	}
	bool operator<(const point & p) const{
		if(x == p.x){
			return y < p.y;
		}else{
			return x < p.x;
		}
	}
	bool operator>(const point & p) const{
		return !(*this == p || *this < p);
	}
};

vector<point> convexHull(vector<point> & points){
	vector<point> L, U;
	for(int i = 0; i < points.size(); i++){
		while(L.size() >= 2 && (L[L.size() - 2] - points[i]).cross(L[L.size() - 1] - points[i]) < 0){
			L.pop_back();
		}
		L.push_back(points[i]);
	}
	for(int i = points.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && (U[U.size() - 2] - points[i]).cross(U[U.size() - 1] - points[i]) < 0){
			U.pop_back();
		}
		U.push_back(points[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}

lli gcd(lli a, lli b){
	lli r;
	while(b){
		r = a % b, a = b, b = r;
	}
	return a;
}

bool collineal(point & a, point & b, point & c){
	return (b - a).cross(c - a) == 0;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m = 0;
	cin >> n;
	vector<point> points(n);
	for(int i = 0; i < n; ++i){
		cin >> points[i].x >> points[i].y;
		points[i].idx = i;
	}
	if(n < 3){
		cout << "0\n";
		return 0;
	}
	bool test = true;
	for(int i = 2; i < n; ++i){
		if(!collineal(points[0], points[1], points[i])){
			test = false;
			break;
		}
	}
	if(test){
		cout << "0\n";
		return 0;
	}
	sort(points.begin(), points.end());
	vector<point> polygon = convexHull(points);
	vector<bool> mem(n + 1, false);
	for(point & p : polygon){
		mem[p.idx] = true;
	}
	vector<point> inside;
	for(point & p : points){
		if(!mem[p.idx]){
			inside.push_back(p);
			++m;
		}
	}
	if(m == 0){
		cout << "1\n";
	}else if(m == 1){
		set<point> vectors;
		int ans = 0;
		for(point & p : polygon){
			point v = p - inside[0];
			if(v.y < 0){
				v.x *= -1;
				v.y *= -1;
			}else if(v.y == 0){
				v.x = abs(v.x);
			}
			lli d = gcd(abs(v.x), abs(v.y));
			v.x /= d;
			v.y /= d;
			if(vectors.count(v)) ans++;
			else vectors.insert(v);
		}
		cout << ans << "\n";
	}else{
		for(int i = 2; i < m; ++i){
			if(!collineal(inside[0], inside[1], inside[i])){
				cout << "0\n";
				return 0;
			}
		}
		for(int i = 0; i < polygon.size(); ++i){
			if(!collineal(inside[0], inside[1], polygon[i])) continue;
			for(int j = 0; j < polygon.size(); ++j){
				if(i == j) continue;
				if(collineal(inside[0], inside[1], polygon[j])){
					cout << "1\n";
					return 0;
				}
			}
		}
		cout << "0\n";
	}
	return 0;
}