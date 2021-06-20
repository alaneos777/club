//#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
using namespace std;
#define endl '\n'
#define __ ios_base::sync_with_stdio(0);cin.tie(0);
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(),(x).end()
typedef long long int lli;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<pii,pii> ppii;

const int mod = (int)998244353;
const int maxn = (int)3e5+5;
const int inf = (int)1e9+10;
const ld EPS = 1e-9;
const ld dinf = 1e9;

bool leq(ld a, ld b){ return b-a >= -EPS;}
bool le(ld a,ld b){ return b-a > EPS;}
bool eq(ld a, ld b){ return abs(a-b) <= EPS;}

struct point{
	ld x,y;

	point(){}
	point(ld x, ld y):x(x),y(y){}

	point operator+(const point &p) const{return point(x+p.x,y+p.y);}
	point operator-(const point &p) const{return point(x-p.x,y-p.y);}
	point operator/(const ld &t) const{return point(x/t,y/t);}
	point operator*(const ld &t) const{return point(x*t,y*t);}

	ld dot(const point &p){
		return x * p.x + y *p.y;
	}

	ld cross(const point &p){
		return x *p.y - y *p.x;
	}

	ld length(){ return sqrtl(x * x + y*y);}
	point unit(){ return (*this)/length();}
};

struct plane{
	point p,pq;
	ld ang;
	plane(){}
	plane(point p, point q): p(p), pq(q - p){
		ang = atan2l(pq.y,pq.x);
	}

	bool out(const point &r){
		return pq.cross(r - p) < -EPS;
	}

	bool operator<(const plane &a){
		if(eq(ang,a.ang)) return pq.cross(a.p -p) < 0;
		return ang < a.ang;
	}

	bool operator==(const plane &a) const{
		return eq(ang,a.ang);
	}
};

pair<int,point> get_intersection(point &a1, point &v1, point &a2, point &v2){
	ld det = v1.cross(v2);
	if(eq(det,0)){
		if(eq((a2 - a1).cross(v1),0))
			return pair<int,point>(-1,point(0,0));
		else
			return pair<int,point>(0,point(0,0));
	}

	point x = a1 + v1 * ((a2 - a1).cross(v2) / det);
	return pair<int,point>(1,x);
}

point inter(plane &s, plane &t){
	point otro = t.pq;
	ld aux = (s.pq).cross(otro);
	ld alpha = (t.p - s.p).cross(t.pq) / aux;
	return s.p + (s.pq * alpha);
}

//con respecto al plano a, la interseccion de b y c NO esta a la izquierda?
bool is_bad(plane &a, plane &b, plane &c){
	int info;
	point x;
	pair<int,point> aux = get_intersection(b.p,b.pq,c.p,c.pq);
	info = aux.first;
	x = aux.second;
	if(info != 1) return false;
	return leq(a.pq.cross(x - a.p),0);//le
}

//siempre se agarra el lado izquierdo del plano dado el vector
vector<point> plane_intersection(vector<plane> &p){
	vector<point> aux;
	aux.push_back(point(-dinf,-dinf));
	aux.push_back(point(dinf,-dinf));
	aux.push_back(point(dinf,dinf));
	aux.push_back(point(-dinf,dinf));

	for(int i=0; i < 4; i++){
		int j = (i+1) % 4;
		p.push_back(plane(aux[i],aux[j]));
	}

	sort(p.begin(),p.end());
	p.erase(unique(p.begin(),p.end()),p.end());

	int n = p.size();
	vector<plane> dq(n+10);
	int s = 1, e = 0;

	for(int i=0; i < n; i++){
		while(s < e && p[i].out(inter(dq[e],dq[e-1]))) e--;
		//while(s < e && is_bad(p[i],dq[e],dq[e-1])) e--;

		while(s < e && p[i].out(inter(dq[s],dq[s+1]))) s++;
		//while(s < e && is_bad(p[i],dq[s],dq[s+1])) s++;
		dq[++e] = p[i];
		
		/*
		//caso especial donde son planos paralelos
		if(s < e && eq(abs(dq[e].pq.cross(dq[e - 1].pq)),0)){
			//si apuntan en lados contrarios
			if(leq(dq[e].pq.dot(dq[e - 1].pq),0)) return vector<point>();
			e--;
			if(leq(p[i].pq.cross(dq[e].p - p[i].p),0)){
				dq[e] = p[i];
			}
		}
		*/
	}

	//while((e-s+1) > 2 && is_bad(dq[s],dq[e],dq[e-1])) e--;
	while((e-s+1) > 2 && dq[s].out(inter(dq[e],dq[e-1]))) e--;
	//while((e-s+1) > 2 && is_bad(dq[e],dq[s],dq[s+1])) s++;
	while((e-s+1) > 2 && dq[e].out(inter(dq[s],dq[s+1]))) s++;

	if((e-s+1) < 3) return vector<point>();
	vector<point> res;
	dq[e+1] = dq[s];
	for(int i=s; i <= e; i++){
		res.push_back(inter(dq[i],dq[i+1]));
	}
	return res;
}

ld get_area(vector<point> &P){
	int n = P.size();
	ld ans = 0.0;
	for(int i=0; i < n; i++){
		int j = (i+1) % n;
		ans+= P[i].cross(P[j]);
	}

	return abs(ans)/2.0;
}


void solve(){
	int n;
	cin >> n;
	vector<point> p(n);
	for(int i=0; i < n; i++){
	    int X,Y;
	    cin >> X >> Y;
	    p[i] = point(X,Y);
		//cin >> p[i].x >> p[i].y;
	}

	reverse(p.begin(),p.end());

	vector<plane> b;
	for(int i=0; i < n; i++){
		int j = (i+1) % n;
		b.push_back(plane(p[i],p[j]));
	}

	vector<point> pol = plane_intersection(b);
	cout << fixed << setprecision(10);
	if(pol.size() == 0){
		cout << 0.0 << endl;
	}
	else{
		cout << get_area(pol) << endl;
	}
}

int main(){__
	int t=1;
	while(t--){
		solve();
	}
	return 0;
}