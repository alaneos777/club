#include <bits/stdc++.h>
#define endl '\n'
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define pb(x) push_back(x)
#define fi first
#define se second
#define all(v) v.begin(), v.end()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

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
	ld appears;
	set<pair<ld, ld>> ranges;
	void read(){cin >> c.x >> c.y >> appears;}
	ld r(ld t) const{
		return max(0.0l, t - appears);
	}
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

int main () {
	/*auto aa = intersect(point(1, 2), 10, point(-8, -6), 7);
	for(point & p : aa){
		cout << p.x << " " << p.y << "\n";
	}exit(0);*/
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n;
	ld target;
	cin >> n >> target;
	vector<circ> circs(n);
	for(circ & ci : circs){
		ci.read();
	}

	auto area = [&](ld t){
		vector<circ> valid;
		for(const circ & curr : circs){
			if(eq(curr.r(t), 0)) continue;
			circ nuevo = curr;
			for(circ & prev : valid){
				if(inside(prev.c, prev.r(t), nuevo.c, nuevo.r(t))){
					nuevo.disable(0, 2*pi);
					//cout << nuevo.c.x << " " << nuevo.c.y << " adentro de " << prev.c.x << " " << prev.c.y << "\n";
				}else if(inside(nuevo.c, nuevo.r(t), prev.c, prev.r(t))){
					prev.disable(0, 2*pi);
					//cout << prev.c.x << " " << prev.c.y << " adentro de " << nuevo.c.x << " " << nuevo.c.y << "\n";
				}else{
					auto cruce = intersect(prev.c, prev.r(t), nuevo.c, nuevo.r(t));
					if(cruce.size() == 2){
						//ccw
						ld a1 = (cruce[0] - prev.c).ang();
						ld a2 = (cruce[1] - prev.c).ang();
						//cw
						ld b1 = (cruce[1] - nuevo.c).ang();
						ld b2 = (cruce[0] - nuevo.c).ang();
						//cout << prev.c.x << " " << prev.c.y << " disable from " << a1*180/pi << " to " << a2*180/pi << "\n";
						//cout << nuevo.c.x << " " << nuevo.c.y << " disable from " << b1*180/pi << " to " << b2*180/pi << "\n\n";
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
				//cout << l*180/pi << " " << r*180/pi << "\n";
				ans += curr.r(t) * (curr.c.x * (sinl(r) - sinl(l)) - curr.c.y * (cosl(r) - cosl(l))) + curr.r(t)*curr.r(t)*(r-l);
			}
			//cout << "\n";
		}
		return ans/2;
	};

	ld l = 0, r = 1e10, t = 0;
	while(abs(l - r) >= eps){
		t = (l + r) / 2;
		if(area(t) >= target){
			r = t;
		}else{
			l = t;
		}
	}

	cout << fixed << setprecision(8) << t << "\n";
	//cout<<area(sqrtl(2));
	return 0;
}