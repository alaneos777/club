#include <bits/stdc++.h>
using namespace std;

double eps = 1e-8;

struct punto{
	double x, y;

	punto(){
		x = y = 0;
	}
	punto(double x, double y){
		this->x = x, this->y = y;
	}

	punto operator+(const punto & p) const{
		return punto(x + p.x, y + p.y);
	}
	punto operator-(const punto & p) const{
		return punto(x - p.x, y - p.y);
	}
	punto operator*(const double & k) const{
		return punto(x * k, y * k);
	}
	punto operator/(const double & k) const{
		return punto(x / k, y / k);
	}

	double dot(const punto & p) const{
		return x * p.x + y * p.y;
	}
	double cross(const punto & p) const{
		return x * p.y - y * p.x;
	}

	bool operator==(const punto & p) const{
		return abs(x - p.x) < eps && abs(y - p.y) < eps;
	}
	bool operator!=(const punto & p) const{
		return !(*this == p);
	}
};

istream &operator>>(istream &is, punto & P){
	punto p;
    is >> p.x >> p.y;
    P = p;
    return is;
}

ostream &operator<<(ostream &os, const punto & p) { 
    return os << fixed << setprecision(2) << p.x << " " << p.y;
}

int main(){
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	cout << "INTERSECTING LINES OUTPUT\n";
	while(n--){
		punto a, b, c, d;
		cin >> a >> b >> c >> d;
		punto v1 = b - a, v2 = d - c;
		double cruz = v1.cross(v2);
		if(abs(cruz) < eps){
			if(abs((a - c).cross(v2)) < eps){
				cout << "LINE";
			}else{
				cout << "NONE";
			}
		}else{
			double t = (c - a).cross(v2) / cruz;
			cout << "POINT " << (a + v1 * t);
		}
		cout << "\n";
	}
	cout << "END OF OUTPUT\n";
	return 0;
}