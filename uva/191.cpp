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

bool intersectSegments(punto & a, punto & b, punto & c, punto & d){
	punto v1 = b - a, v2 = d - c;
	double det = v1.cross(v2);
	if(abs(det) < eps){
		if(abs((a - c).cross(v2)) < eps){
			if(v1 == punto(0, 0)){
				if(v2 == punto(0, 0)){
					return a == c;
				}else{
					double u = (a - c).dot(v2) / v2.dot(v2);
					return -eps <= u && u <= (1 + eps);
				}
			}else{
				double k = v2.dot(v1) / v1.dot(v1);
				double p = (a - c).dot(v1) / v1.dot(v1);
				double lower = p / k, upper = (p + 1) / k;
				if(lower > upper) swap(lower, upper);
				return -eps <= upper && lower <= (1 + eps);
			}
		}else{
			return false;
		}
	}else{
		double t = (c - a).cross(v2) / det;
		double u = (c - a).cross(v1) / det;
		return -eps <= t && t <= (1 + eps) && -eps <= u && u <= (1 + eps);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	while(n--){
		punto a, b, esq1, esq2, esq3, esq4;
		cin >> a >> b >> esq1 >> esq3;
		double x0 = min(esq1.x, esq3.x), y0 = min(esq1.y, esq3.y);
		double w = abs(esq1.x - esq3.x), h = abs(esq1.y - esq3.y);
		esq2 = punto(esq3.x, esq1.y);
		esq4 = punto(esq1.x, esq3.y);
		if(intersectSegments(a, b, esq1, esq2) || intersectSegments(a, b, esq2, esq3) || intersectSegments(a, b, esq3, esq4) || intersectSegments(a, b, esq4, esq1)){
			cout << "T\n";
		}else{
			if((x0 <= a.x && a.x <= x0 + w && y0 <= a.y && a.y <= y0 + h) || (x0 <= b.x && b.x <= x0 + w && y0 <= b.y && b.y <= y0 + h)){
				cout << "T\n";
			}else{
				cout << "F\n";
			}
		}
	}
	return 0;
}