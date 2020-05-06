#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const ld eps = 1e-9;
const ld pi = acosl(-1);

bool ge(ld a, ld b){return a-b > eps;}
bool le(ld a, ld b){return b-a > eps;}
bool eq(ld a, ld b){return abs(a-b) <= eps;}

struct point{
	ld x, y;
	point(): x(0), y(0) {}
	point(ld x, ld y): x(x), y(y) {}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x*k, y*k);}
	point operator/(const ld & k) const{return point(x/k, y/k);}
	ld ang() const{
		ld ans = atan2l(y, x);
		if(le(ans, 0)) ans += 2*pi;
		return ans;
	}
	ld length() const{
		return sqrtl(x*x + y*y);
	}
	ld norm() const{
		return (x*x + y*y);
	}
	point perp() const{return point(-y, x);}
};

struct circ{
	point c;
	ld r;
	set<pair<ld, ld>> ranges;
	void read(){cin >> c.x >> c.y >> r;}

	void disable(ld l, ld r){
		ranges.emplace(l, r);
	}
	auto getActive() const{
		vector<pair<ld, ld>> ans;
		ld maxi = 0;
		for(const auto & dis : ranges){
			ld l, r;
			tie(l, r) = dis;
			if(l > maxi){
				ans.emplace_back(maxi, l);
			}
			maxi = max(maxi, r);
		}
		if(!eq(maxi, 2*pi)){
			ans.emplace_back(maxi, 2*pi);
		}
		return ans;
	}
};

int inside(const point & c1, ld r1, const point & c2, ld r2){
	ld l = r1 - r2 - (c1 - c2).length();
	return (ge(l, 0) ? 1 : (eq(l, 0) ? -1 : 0));
}

vector<point> intersect(const point & c1, ld r1, const point & c2, ld r2){
	point d = c2 - c1;
	ld d2 = d.norm();
	if(eq(d2, 0)) return {};
	ld pd = (d2 + r1*r1 - r2*r2) / 2;
	ld h2 = r1*r1 - pd*pd/d2;
	point p = c1 + d*pd/d2;
	if(eq(h2, 0)) return {p};
	else if(le(h2, 0)) return {};
	else{
		point u = d.perp() * sqrt(h2/d2);
		return {p - u, p + u};
	}
}

ld area(const vector<circ> & circs){
	vector<circ> valid;
	for(const circ & curr : circs){
		if(eq(curr.r, 0)) continue;
		circ nuevo = curr;
		for(circ & prev : valid){
			if(inside(prev.c, prev.r, nuevo.c, nuevo.r)){
				nuevo.disable(0, 2*pi);
			}else if(inside(nuevo.c, nuevo.r, prev.c, prev.r)){
				prev.disable(0, 2*pi);
			}else{
				auto cruce = intersect(prev.c, prev.r, nuevo.c, nuevo.r);
				if(cruce.size() == 2){
					ld a1 = (cruce[0] - prev.c).ang();
					ld a2 = (cruce[1] - prev.c).ang();
					ld b1 = (cruce[1] - nuevo.c).ang();
					ld b2 = (cruce[0] - nuevo.c).ang();
					if(a1 < a2){
						prev.disable(a1, a2);
					}else{
						prev.disable(a1, 2*pi);
						prev.disable(0, a2);
					}
					if(b1 < b2){
						nuevo.disable(b1, b2);
					}else{
						nuevo.disable(b1, 2*pi);
						nuevo.disable(0, b2);
					}
				}
			}
		}
		valid.push_back(nuevo);
	}
	ld ans = 0;
	for(const circ & curr : valid){
		for(const auto & range : curr.getActive()){
			ld l, r;
			tie(l, r) = range;
			ans += curr.r * (curr.c.x * (sinl(r) - sinl(l)) - curr.c.y * (cosl(r) - cosl(l))) + curr.r*curr.r*(r-l);
		}
	}
	return ans/2;
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<circ> circs(n);
	for(circ & curr : circs){
		curr.read();
	}
	cout << fixed << setprecision(5) << area(circs) << "\n";
	return 0;
}