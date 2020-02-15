#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-13;
const ld pi = acosl(-1);

bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

struct point{
	ld x, y;
	point(): x(0), y(0) {}
	point(ld x, ld y): x(x), y(y) {}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	ld cross(const point & p) const{return x * p.y - y * p.x;}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
};

vector<point> convexHull(vector<point> P){
	sort(P.begin(), P.end());
	vector<point> L, U;
	for(int i = 0; i < P.size(); i++){
		while(L.size() >= 2 && leq((L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]), 0)){
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	for(int i = P.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && leq((U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]), 0)){
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}

vector<point> minkowskiSum(vector<point> A, vector<point> B){
	int na = (int)A.size(), nb = (int)B.size();
	if(A.empty() || B.empty()) return {};

	rotate(A.begin(), min_element(A.begin(), A.end()), A.end());
	rotate(B.begin(), min_element(B.begin(), B.end()), B.end());

	int pa = 0, pb = 0;
	vector<point> M;

	while(pa < na && pb < nb){
		M.push_back(A[pa] + B[pb]);
		ld x = (A[(pa + 1) % na] - A[pa]).cross(B[(pb + 1) % nb] - B[pb]);
		if(leq(x, 0)) pb++;
		if(geq(x, 0)) pa++;
	}

	while(pa < na) M.push_back(A[pa++] + B[0]);
	while(pb < nb) M.push_back(B[pb++] + A[0]);

	return M;
}

vector<point> gen(int n){
	vector<point> P(n);
	for(int i = 0; i < n; ++i){
		ld ang = (2*i-1) * pi / n;
		P[i].x = cosl(ang);
		P[i].y = sinl(ang);
	}
	return P;
}

ld area(vector<point> P){
	ld ans = 0;
	int n = P.size();
	for(int i = 0; i < n; ++i){
		ans += P[i].cross(P[(i+1)%n]);
	}
	return abs(ans/2);
}

int main(){
	vector<point> P = {point(0, 0)};
	for(int i = 1864; i <= 1909; ++i){
		P = convexHull(minkowskiSum(P, gen(i)));
	}
	cout << P.size() << "\n";
	cout << fixed << setprecision(6) << area(P) << "\n";
	return 0;
}