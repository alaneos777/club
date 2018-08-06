#include <bits/stdc++.h>
using namespace std;

struct point{
	double x, y;
	point():x(0),y(0){}
	point(double x, double y):x(x),y(y){}
	point operator+(const point &p) const{
		return point(x + p.x, y + p.y);
	}
	point operator/(const double &k) const{
		return point(x / k, y / k);
	}
	double operator*(const point &p) const{
		return x * p.y - y * p.x;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	double L;
	cin >> t;
	while(t--){
		cin >> L;
		point A(0, L), B(0, 0), C(L, 0), D(L, L), E(L / 2.0, L * (sqrt(3) / 2 + 1));
		point P = (A + B + E) / 3, Q = (B + C + E) / 3, R = (C + D + E) / 3, S = (D + A + E) / 3;
		double area = (P*Q + Q*R + R*S + S*P) / 2;
		stringstream ss;
		ss << fixed << setprecision(3) << abs(area);
		string ans = ss.str();
		replace(ans.begin(), ans.end(), '.', ',');
		cout << ans << "\n";
	}
	return 0;
}