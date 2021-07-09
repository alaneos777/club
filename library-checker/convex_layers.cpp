#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct point{
	lli x, y;
	int id;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y) {}
	point operator+(const point& p) const{return point(x - p.x, y - p.y);}
	point operator-(const point& p) const{return point(x - p.x, y - p.y);}
	lli dot(const point& p) const{return x * p.x + y * p.y;}
	lli cross(const point& p) const{return x * p.y - y * p.x;}
	bool operator==(const point& p) const{return x == p.x && y == p.y;}
	bool operator<(const point& p) const{return x < p.x || (x == p.x && y < p.y);}
};

istream& operator>>(istream& is, point& p){
	return is >> p.x >> p.y;
}

auto convexHull(const set<point>& P){
	int n = P.size();
	if(n <= 2) return vector<point>(P.begin(), P.end());
	vector<point> lo, hi;
	for(const point& p : P){
		while(lo.size() >= 2 && (lo[lo.size()-1] - lo[lo.size()-2]).cross(p - lo[lo.size()-1]) < 0) lo.pop_back();
		lo.push_back(p);
	}
	for(auto it = P.rbegin(); it != P.rend(); ++it){
		point p = *it;
		while(hi.size() >= 2 && (hi[hi.size()-1] - hi[hi.size()-2]).cross(p - hi[hi.size()-1]) < 0) hi.pop_back();
		hi.push_back(p);
	}
	lo.pop_back(), hi.pop_back();
	lo.insert(lo.end(), hi.begin(), hi.end());
	return lo;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	set<point> P;
	for(int i = 0; i < n; ++i){
		point p;
		cin >> p;
		p.id = i;
		P.insert(p);
	}
	vector<int> ans(n);
	int layer = 1;
	while(!P.empty()){
		auto curr = convexHull(P);
		for(const point& p : curr){
			ans[p.id] = layer;
			P.erase(p);
		}
		layer++;
	}
	for(int i = 0; i < n; ++i){
		cout << ans[i] << "\n";
	}
	return 0;
}