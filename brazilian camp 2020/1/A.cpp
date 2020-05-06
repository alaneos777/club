#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld pi = acosl(-1);
const ld eps = 1e-8;

ld eq(ld a, ld b){return abs(a-b)<eps;}
ld le(ld a, ld b){return a-b<-eps;}
ld ge(ld a, ld b){return a-b>eps;}
ld geq(ld a, ld b){return a-b>-eps;}

struct point{
	ld x, y, z;
	point(): x(0), y(0), z(0){}
	point(ld x, ld y, ld z): x(x), y(y), z(z){}
	point(ld phi, ld theta): x(cosl(phi)*cosl(theta)), y(cosl(phi)*sinl(theta)), z(sinl(phi)){}
	point operator+(const point & p) const{return point(x+p.x, y+p.y, z+p.z);}
	point operator-(const point & p) const{return point(x-p.x, y-p.y, z-p.z);}
	point operator*(const ld & k) const{return point(x*k, y*k, z*k);}
	point operator/(const ld & k) const{return point(x/k, y/k, z/k);}
	ld dot(const point & p) const{return x*p.x + y*p.y + z*p.z;}
	point cross(const point & p) const{return point(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);}
	ld length() const{return sqrtl(x*x + y*y + z*z);}
	point unit() const{
		ld l = length();
		return point(x/l, y/l, z/l);
	}
};

ld arccos(ld x){
	return acosl(max(-1.0l, min(1.0l, x)));
}

ld ang_between(const point & a, const point & b){
	ld cos_x = a.dot(b) / a.length() / b.length();
	return arccos(cos_x);
}

vector<point> point_tangency(const point & O, ld r, const point & p, ld R){
	point u1 = (p - O * O.dot(p)).unit();
	point u2 = O.cross(u1);
	ld theta = arccos(p.dot(O)*tanl(r/R)/p.dot(u1));
	return {(O*cosl(r/R) + (u1*cosl(theta) + u2*sinl(theta))*sinl(r/R)) * R,
	(O*cosl(r/R) + (u1*cosl(theta) - u2*sinl(theta))*sinl(r/R)) * R};
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ld phi_a, theta_a, phi_b, theta_b, phi_o, theta_o, r, R;
	cin >> phi_a >> theta_a >> phi_b >> theta_b >> phi_o >> theta_o >> r >> R;
	cout << fixed << setprecision(10);
	point A = point(phi_a*pi/180, theta_a*pi/180);
	point B = point(phi_b*pi/180, theta_b*pi/180);
	point O = point(phi_o*pi/180, theta_o*pi/180);
	ld ang = ang_between(A, B);
	if(eq(ang, pi)){
		cout << ang*R << "\n";
		return 0;
	}
	point n = A.cross(B).unit();
	point u = A, v = n.cross(A); //arc: u*cos(t) + v*sin(t) , 0 <= t <= ang
	point proj = (O - n * O.dot(n)).unit();
	//tan(t) = proj.v / proj.u
	ld t = atan2l(proj.dot(v), proj.dot(u));
	if(le(t, 0)) t += 2*pi;
	if(ge(t, ang)){
		cout << ang*R << "\n";
		return 0;
	}
	ld dist = ang_between(O, proj) * R;
	if(geq(dist, r)){
		cout << ang*R << "\n";
		return 0;
	}
	auto t_a = point_tangency(O, r, A, R);
	auto t_b = point_tangency(O, r, B, R);
	ld ans = numeric_limits<ld>::max();
	ld rr = R*sinl(r/R);
	point pr = O * R * cosl(r/R);
	for(point lhs : t_a){
		for(point rhs : t_b){
			ans = min(ans, ang_between(A, lhs)*R + ang_between(lhs-pr, rhs-pr)*rr + ang_between(rhs, B)*R);
		}
	}
	cout << ans << "\n";
	return 0;
}

// https://math.stackexchange.com/questions/1303943/tangent-points-on-circle-that-placed-on-earth-surface