#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct point{
	lli x, y;
	point(): x(0), y(0) {}
	point(lli x, lli y): x(x), y(y) {}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	lli dot(const point & p) const{return x * p.x + y * p.y;}
	lli cross(const point & p) const{return x * p.y - y * p.x;}
	lli len() const{return x*x + y*y;}
	bool operator==(const point & p) const{return x == p.x && y == p.y;}
	bool operator<(const point & p) const{return x < p.x || (x == p.x && y < p.y);}
};

vector<point> minkowskiSum(vector<point> A, vector<point> B){
	int na = (int)A.size(), nb = (int)B.size();
	if(A.empty() || B.empty()) return {};

	rotate(A.begin(), min_element(A.begin(), A.end()), A.end());
	rotate(B.begin(), min_element(B.begin(), B.end()), B.end());

	int pa = 0, pb = 0;
	vector<point> M;

	while(pa < na && pb < nb){
		M.push_back(A[pa] + B[pb]);
		lli x = (A[(pa + 1) % na] - A[pa]).cross(B[(pb + 1) % nb] - B[pb]);
		if(x <= 0) pb++;
		if(x >= 0) pa++;
	}

	while(pa < na) M.push_back(A[pa++] + B[0]);
	while(pb < nb) M.push_back(B[pb++] + A[0]);

	return M;
}

vector<point> ch(vector<point> P){
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

point Ratio(const vector<point> & P, const vector<point> & T, int i){
	int n = P.size();
	lli num = (P[(i+1)%n] - P[i]).len(), den = (T[(i+1)%n] - T[i]).len(), d = __gcd(num, den);
	return point(num / d, den / d);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<point> P(n), Q(n);
	for(int i = 0; i < n; ++i){
		cin >> P[i].x >> P[i].y;
		Q[i].x = -P[i].x, Q[i].y = -P[i].y;
	}
	auto T = ch(minkowskiSum(P, Q));
	rotate(P.begin(), min_element(P.begin(), P.end()), P.end());
	rotate(T.begin(), min_element(T.begin(), T.end()), T.end());
	if(T.size() == n){
		point r = Ratio(P, T, 0);
		bool similar = true;
		for(int i = 1; i < n; ++i){
			similar &= (r == Ratio(P, T, i));
		}
		if(similar){
			cout << "YES\n";
		}else{
			cout << "NO\n";
		}
	}else{
		cout << "NO\n";
	}
	return 0;
}