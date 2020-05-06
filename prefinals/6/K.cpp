#include <bits/stdc++.h>
using namespace std;
using lli = long long;
using ld = long double;

struct point{
	lli x, y, z;
	point(): x(0), y(0), z(0) {}
	point(lli x, lli y, lli z): x(x), y(y), z(z) {}

	point operator+(const point & p) const{return point(x+p.x, y+p.y, z+p.z);}
	point operator+=(const point & p){*this = *this + p; return *this;}
	point operator-(const point & p) const{return point(x-p.x, y-p.y, z-p.z);}

	ld len() const{return x*x + y*y + z*z;}
	lli dot(const point & p) const{return x*p.x + y*p.y + z*p.z;}
	point cross(const point & p) const{return point(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);}

	bool operator==(const point & p) const{return x == p.x && y == p.y && z == p.z;}
	bool operator<(const point & p) const{return x < p.x || (x == p.x && y < p.y);}
};

ld variance(const vector<point> & points){
	int n = points.size();
	if(n == 0) return 0;
	ld p2 = 0;
	point s;
	for(int i = 0; i < n; ++i){
		p2 += points[i].len();
		s += points[i];
	}
	return p2 - s.len() / n;
}

ld variance(const vector<int> & idxs, const vector<point> & points){
	int n = idxs.size();
	if(n == 0) return 0;
	ld p2 = 0;
	point s;
	for(int i = 0; i < n; ++i){
		p2 += points[idxs[i]].len();
		s += points[idxs[i]];
	}
	return p2 - s.len() / n;
}

ld brute(const vector<point> & points){
	int n = points.size();
	ld ans = 1e18;
	for(int mask = 0; mask < (1<<n); ++mask){
		vector<point> A, B;
		for(int i = 0; i < n; ++i){
			if(mask & (1<<i)){
				A.push_back(points[i]);
			}else{
				B.push_back(points[i]);
			}
		}
		ans = min(ans, variance(A) + variance(B));
	}
	return ans;
}

ld solve(const vector<point> & points){
	auto p = points;
	sort(p.begin(), p.end());
	p.erase(unique(p.begin(), p.end()), p.end());
	int n = p.size();
	ld ans = 1e18;
	vector<int> arriba, abajo, enmedio;
	for(int i = 0; i < n-2; ++i){
		for(int j = i+1; j < n-1; ++j){
			for(int k = j+1; k < n; ++k){
				arriba.clear(), abajo.clear(), enmedio.clear();
				point u = (p[j] - p[i]).cross(p[k] - p[i]);
				for(int l = 0; l < points.size(); ++l){
					lli side = u.dot(points[l] - p[i]);
					if(side > 0){
						arriba.push_back(l);
					}else if(side < 0){
						abajo.push_back(l);
					}else{
						enmedio.push_back(l);
					}
				}
				int m = enmedio.size();
				for(int mask = 0; mask < (1<<m); ++mask){
					int sz_arriba = 0, sz_abajo = 0;
					for(int l = 0; l < m; ++l){
						if(mask & (1<<l)){
							arriba.push_back(enmedio[l]);
							sz_arriba++;
						}else{
							abajo.push_back(enmedio[l]);
							sz_abajo++;
						}
					}
					ans = min(ans, variance(arriba, points) + variance(abajo, points));
					while(sz_arriba--) arriba.pop_back();
					while(sz_abajo--) abajo.pop_back();
				}
			}
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<point> points(n);
	for(int i = 0; i < n; ++i){
		cin >> points[i].x >> points[i].y >> points[i].z;
	}
	ld ans = 0;
	if(n == 1){
		ans = 0;
	}else if(k == 1){
		ans = variance(points);
	}else if(n == 2 && k == 2){
		ans = 0;
	}else if(n <= 20){
		ans = brute(points);
	}else{
		ans = solve(points);
	}
	cout << fixed << setprecision(10) << ans << "\n";
	return 0;
}