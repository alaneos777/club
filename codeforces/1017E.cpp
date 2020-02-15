#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

bool eq(ld a, ld b){return abs(a-b) <= 1e-9;}

struct point{
	lli x, y;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y){}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	lli dot(const point & p) const{return x*p.x + y*p.y;}
	lli cross(const point & p) const{return x*p.y - y*p.x;}
	ld length() const{return sqrtl(x*x + y*y);}
	bool operator<(const point & p) const{
		if(x != p.x) return x < p.x;
		return y < p.y;
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

istream&operator>>(istream & is, point & p){
	return is >> p.x >> p.y;
}


vector<int> kmp_table(const vector<pair<ld, lli>> & pattern){
	vector<int> aux(pattern.size());
	int i = 1, j = 0;
	while(i < pattern.size()){
		if(eq(pattern[i].first, pattern[j].first) && pattern[i].second == pattern[j].second)
			aux[i++] = ++j;
		else{
			if(j == 0) aux[i++] = 0;
			else j = aux[j - 1];
		}
	}
	return aux;
}

bool search(const vector<pair<ld, lli>> & pattern, const vector<pair<ld, lli>> & text){
	vector<int> aux = kmp_table(pattern);
	int i = 0, j = 0;
	while(i < text.size() && j < pattern.size()){
		if(text[i] == pattern[j]){
			++i, ++j;
			if(j == pattern.size()){
				return true;
			}
		}else{
			if(j == 0) ++i;
			else j = aux[j - 1];
		}
	}
	return false;
}

ld arccos(ld x){
	return acosl(max(-1.0l, min(1.0l, x)));
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<point> a(n), b(m);
	for(point & p : a) cin >> p;
	for(point & p : b) cin >> p;
	a = convexHull(a), b = convexHull(b);
	n = a.size(), m = b.size();
	if(n != m){
		cout << "NO";
		return 0;
	}
	vector<pair<ld, lli>> lst_a, lst_b;
	for(int i = 0; i < n; ++i){
		point u = a[(i+1)%n] - a[i];
		point v = a[(i+2)%n] - a[(i+1)%n];
		lst_a.emplace_back(arccos((ld)u.dot(v) / u.length() / v.length()), u.dot(u));
	}
	for(int i = 0; i < n; ++i){
		lst_a.push_back(lst_a[i]);
		point u = b[(i+1)%n] - b[i];
		point v = b[(i+2)%n] - b[(i+1)%n];
		lst_b.emplace_back(arccos((ld)u.dot(v) / u.length() / v.length()), u.dot(u));
	}
	cout << (search(lst_b, lst_a) ? "YES": "NO") << "\n";
	return 0;
}