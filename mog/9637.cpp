#include <bits/stdc++.h>
using namespace std;
using ld = long double;

struct point{
	ld x, y;
	int id, rank;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}
	point operator+(const point & p) const{return {x + p.x, y + p.y};}
	point operator-(const point & p) const{return {x - p.x, y - p.y};}
	ld cross(const point & p) const{return x*p.y - y*p.x;}
	point normalize() const{
		ld l = sqrtl(x*x + y*y);
		return point(x/l, y/l);
	}
	bool operator<(const point & p) const{
		if(x != p.x) return x < p.x;
		return y < p.y;
	}
};

istream &operator>>(istream & is, point & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream & os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}

vector<point> convexHull(vector<point> & P){
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

ld dist(const point & a, const point & v, const point & p){
	return (p - a).cross(v);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<point> points(n);
	for(int i = 0; i < n; ++i){
		cin >> points[i] >> points[i].rank;
		points[i].id = i;
	}
	vector<point> rem = points;
	sort(rem.begin(), rem.end());
	vector<pair<point, point>> lines;
	while(rem.size() >= 3){
		vector<point> perimeter = convexHull(rem);
		int idx = -1, rank_max = -1;
		for(int i = 0; i < perimeter.size(); ++i){
			if(perimeter[i].rank > rank_max){
				rank_max = perimeter[i].rank;
				idx = i;
			}
		}
		point P = perimeter[idx];
		point A = perimeter[(idx-1+perimeter.size())%perimeter.size()];
		point B = perimeter[(idx+1)%perimeter.size()];
		lines.emplace_back(P, (A-P).normalize());
		lines.emplace_back(P, (B-P).normalize());
		rem.erase(rem.begin() + perimeter[idx].id);
	}
	lines.emplace_back(rem[0], (rem[1]-rem[0]).normalize());
	bool ans = false;
	for(const auto & line : lines){
		bool valid = true;
		vector<pair<ld, int>> dists;
		for(int i = 0; i < n; ++i){
			dists.emplace_back(dist(line.first, line.second, points[i]), points[i].rank);
		}
		sort(dists.begin(), dists.end());
		int idx = 0;
		while(idx < n-1 && dists[idx].second == dists[idx+1].second){
			idx++;
		}
		if(idx != n-1){
			int sgn = dists[idx].second - dists[idx+1].second;
			for(int i = idx+1; i < n-1; ++i){
				int sgn2 = dists[i].second - dists[i+1].second;
				valid = valid & !((sgn < 0 && sgn2 > 0) || (sgn > 0 && sgn2 < 0));
			}
		}
		ans = ans | valid;
		if(ans) break;
	}
	if(ans) cout << "Y\n";
	else cout << "N\n";
	return 0;
}