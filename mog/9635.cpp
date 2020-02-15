#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

const ld eps = 0.5e-13;
const ld pi = acosl(-1);

struct point{
	lli x, y;
	ld A, alpha1, alpha2;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y){}
	lli norm() const{return x*x + y*y;}
	ld length() const{return sqrtl(norm());}
	void move(){
		while(!(x >= 0 && y >= 0)){
			swap(x, y);
			y = -y;
		}
	}
	void calc(){
		A = sqrtl(2) * length();
		alpha1 = atan2l(y + x, y - x);
		alpha2 = atan2l(-y - x, x - y);
	}
};

bool eq(ld a, ld b){return abs(a-b) < eps;}
bool le(ld a, ld b){return a-b < -eps;}
bool ge(ld a, ld b){return a-b > eps;}

istream& operator>>(istream & is, point & p){
	return is >> p.x >> p.y;
}

struct event{
	ld val;
	int type;
	int id;
	event(): val(0), type(0), id(-1){};
	event(ld val, int type): val(val), type(type){}
	event(ld val, int type, int id): val(val), type(type), id(id){}
	bool operator<(const event & e) const{
		if(!eq(val, e.val)) return le(val, e.val);
		return type > e.type;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	lli mini = numeric_limits<lli>::max();
	vector<point> points(n);
	for(point & p : points){
		cin >> p;
		p.move();
		p.calc();
		mini = min(mini, p.norm());
	}

	auto can = [&](ld R){
		vector<event> events;
		int cnt = 0;
		for(const point & p : points){
			// (y-x)*sin(t) + (x+y)*cos(t) >= R or (x+y)*sin(t) + (x-y)*cos(t) >= R
			// y-x=A*cos(alpha), x+y=A*sin(alpha) , A = sqrt(2)sqrt(x^2+y^2) , tan(alpha) = (y+x)/(y-x) , tan(alpha-pi) = (-y-x)/(x-y)
			// sin(t + alpha1) >= R/A
			// cos(t + alpha2) >= R/A
			ld rhs = R/p.A;
			if(ge(rhs, 1)){
				return false;
			}
			ld theta1 = asinl(min(rhs, 1.0l));
			ld theta2 = acosl(min(rhs, 1.0l));
			ld a = max(0.0l, theta1 - p.alpha1);
			ld b = min(pi/2, pi - theta1 - p.alpha1);
			ld c = max(0.0l, -theta2 - p.alpha2);
			ld d = min(pi/2, theta2 - p.alpha2);
			if(ge(a, b)){
				if(ge(c, d)){
					return false;
				}
				events.emplace_back(c, 1, cnt);
				events.emplace_back(d, 0, cnt++);
			}else{
				if(ge(c, d)){
					events.emplace_back(a, 1, cnt);
					events.emplace_back(b, 0, cnt++);
				}else{
					if(ge(a, c)){
						swap(a, c);
						swap(b, d);
					}
					if(le(b, c)){
						events.emplace_back(a, 1, cnt);
						events.emplace_back(b, 0, cnt++);
						events.emplace_back(c, 1, cnt);
						events.emplace_back(d, 0, cnt++);
					}else{
						events.emplace_back(a, 1, cnt);
						events.emplace_back(max(b, d), cnt++);
					}
				}
			}
		}
		sort(events.begin(), events.end());
		set<int> active;
		for(const event & e : events){
			if(active.size() == points.size()){
				return true;
			}
			if(e.type == 1){
				active.insert(e.id);
			}else{
				assert(active.erase(e.id));
			}
		}
		return false;
	};

	ld l = sqrtl(mini), r = sqrtl(2*mini), med;
	while(abs(l - r) >= 1e-10){
		med = (l + r) / 2;
		if(can(med)) l = med;
		else r = med;
	}
	cout << fixed << setprecision(4) << med*sqrtl(32) << "\n";
	return 0;
}