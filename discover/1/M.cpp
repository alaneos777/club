#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
using ld = long double;
const ld eps = 1e-9;
bool le(ld a, ld b){return a - b < -eps;}
bool leq(ld a, ld b){return a - b <= eps;}

ld valid(ld x){
	return leq(0, x) && leq(x, 1);
}

using pt = pair<ld, ld>;
ld dis(pt a, pt b){
	return hypotl(a.first - b.first, a.second - b.second);
}

bool go(pt A, pt B, pt C){
	ld c = dis(A, B);
	ld b = dis(A, C);
	ld a = dis(B, C);
	ld P = a+b+c;
	ld d = P*P - 8*b*c;
	if(le(d, 0)) return false;
	ld x1 = (P + sqrtl(abs(d))) / (4*c);
	ld x2 = (P - sqrtl(abs(d))) / (4*c);
	ld y1 = (P - 2*c*x1) / (2*b);
	ld y2 = (P - 2*c*x2) / (2*b);
	ld x, y;
	if(valid(x1) && valid(y1)){
		x = x1, y = y1;
	}else if(valid(x2) && valid(y2)){
		x = x2, y = y2;
	}else{
		return false;
	}
	cout << fixed << setprecision(10) << A.first+(B.first-A.first)*x << " " << A.second+(B.second-A.second)*x << "\n";
	cout << fixed << setprecision(10) << A.first+(C.first-A.first)*y << " " << A.second+(C.second-A.second)*y << "\n";
	return true;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ld a, b, c;
	cin >> a >> b >> c;
	if(!(go({0, 0}, {a, b}, {c, 0}) || go({a, b}, {0, 0}, {c, 0}) || go({c, 0}, {a, b}, {0, 0}))){
		cout << "Impossible\n";
	}
	return 0;
}