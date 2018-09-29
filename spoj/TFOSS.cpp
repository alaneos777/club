#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct point{
	lli x, y;

	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y){}

	void read(){cin >> x >> y;}

	point operator-(const point & p) const{
		return point(x - p.x, y - p.y);
	}

	bool operator<(const point & p) const{
		if(x == p.x) return y < p.y;
		return x < p.x;
	}

	lli cross(const point & p) const{
		return x * p.y - y * p.x;
	}

	lli norm() const{
		return x * x + y * y;
	}
};

vector<point> convexHull(vector<point> & P){
	sort(P.begin(), P.end());
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

vector<pair<int, int>> antipodalPairs(vector<point> & P){
	vector<pair<int, int>> ans;
	int n = P.size(), k = 1;
	auto f = [&](int u, int v, int w){return abs((P[v%n]-P[u%n]).cross(P[w%n]-P[u%n]));};
	while(f(n-1, 0, k+1) > f(n-1, 0, k)) ++k;
	for(int i = 0, j = k; i <= k && j < n; ++i){
		ans.emplace_back(i, j);
		while(j < n-1 && f(i, i+1, j+1) > f(i, i+1, j)){
			ans.emplace_back(i, j+1);
			++j;
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int c;
		cin >> c;
		vector<point> points(c);
		for(int i = 0; i < c; ++i){
			points[i].read();
		}
		if(c == 1){
			cout << "0\n";
		}else if(c == 2){
			cout << (points[0] - points[1]).norm() << "\n";
		}else{
			points = convexHull(points);
			auto pairs = antipodalPairs(points);
			lli ans = 0;
			for(auto & pair : pairs){
				ans = max(ans, (points[pair.first] - points[pair.second]).norm());
			}
			cout << ans << "\n";
		}
	}
	return 0;
}