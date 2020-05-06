#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct point{
	lli x, y;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y){}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const lli & k) const{return point(x * k, y * k);}
	lli cross(const point & p) const{return x * p.y - y * p.x;}
	bool half() const{return y < 0 || (y == 0 && x < 0);}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n;
	vector<point> points(n);
	for(point & p : points){
		cin >> p.x >> p.y;
	}
	points.resize(2*n);
	vector<vector<int>> acum(n, vector<int>(2*n));
	vector<int> positions;

	for(int i = 0; i < n; ++i){
		positions.clear();
		for(int j = 0; j < n; ++j){
			if(i != j){
				positions.push_back(j);
				positions.push_back(j + n);
			}
			points[j+n] = points[i]*2 - points[j];
		}
		sort(positions.begin(), positions.end(), [&](int a, int b){
			point u = points[a] - points[i];
			point v = points[b] - points[i];
			return make_pair(u.half(), 0ll) < make_pair(v.half(), u.cross(v));
		});
		for(int j = 0; j < 2*(n-1); ++j){
			acum[i][positions[j]] = j+1;
		}
	}

	points.resize(n);

	auto cnt = [&](int a, int b, int c){
		point u = points[b] - points[a];
		point v = points[c] - points[a];
		if(u.cross(v) < 0){
			swap(b, c);
			swap(u, v);
		}
		if(make_pair(u.half(), 0ll) < make_pair(v.half(), u.cross(v))){
			return acum[a][c] - acum[a][b] - 1;
		}else{
			return 2*n-3 - (acum[a][b] - acum[a][c]);
		}
	};

	cin >> q;
	while(q--){
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b, --c;
		int ans = cnt(a, b, c) + cnt(b, a, c) + cnt(c, a, b) - n + 3;
		ans = ans / 2;
		cout << ans << "\n";
	}
	return 0;
}