#include <bits/stdc++.h>
using namespace std;

struct point{
	int x, y;
	point(): x(0), y(0) {}
	point(int x, int y): x(x), y(y) {}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	int cross(const point & p) const{return x*p.y - y*p.x;}
	bool operator<(const point & p) const{
		if(x != p.x) return x < p.x;
		return y < p.y;
	}
	bool operator==(const point & p) const{
		return x == p.x && y == p.y;
	}
};

istream&operator>>(istream & is, point & p){
	return is >> p.x >> p.y;
}

ostream&operator<<(ostream & os, const point & p){
	return os << p.x << " " << p.y;
}

vector<point> convexHull(vector<point> & P){
	vector<point> L, U;
	sort(P.begin(), P.end());
	P.erase(unique(P.begin(), P.end()), P.end());
	int n = P.size();
	if(n <= 2) return P;
	
	for(int i = 0; i < n; ++i){
		while(L.size() >= 2 && (L[L.size()-1] - L[L.size()-2]).cross(P[i] - L[L.size()-1]) <= 0){
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	
	for(int i = n-1; i >= 0; --i){
		while(U.size() >= 2 && (U[U.size()-1] - U[U.size()-2]).cross(P[i] - U[U.size()-1]) <= 0){
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	
	L.pop_back(), U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	while(cin >> n && n != 0){
		vector<point> P(n);
		for(point & p : P){
			cin >> p;
		}
		P = convexHull(P);
		cout << P.size() << "\n";
		for(const point & p : P){
			cout << p << "\n";
		}
	}
	return 0;
}