#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);

double eval(vector<double> & p, double x0){
	double res = 0;
	for(int i = p.size()-1; i >= 0; --i){
		res = res * x0 + p[i];
	}
	return res;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		int deg, slices, stacks;
		double a, b;
		cin >> deg;
		vector<double> poly(deg + 1);
		for(int i = 0; i <= deg; ++i){
			cin >> poly[deg - i];
		}
		cin >> a >> b >> slices >> stacks;
		vector<double> polysq(2*deg + 1), polysqint(2*deg + 2);
		for(int i = 0; i <= deg; ++i){
			for(int j = 0; j <= deg; ++j){
				polysq[i + j] += poly[i] * poly[j];
			}
		}
		for(int i = 0; i <= 2*deg; ++i){
			polysqint[i + 1] = polysq[i] / (i + 1);
		}
		double real = pi * (eval(polysqint, b) - eval(polysqint, a));
		double approx = 0;
		double dx = (b - a) / stacks;
		for(int i = 0; i < stacks; ++i){
			double fa = eval(poly, a + dx * i);
			double fb = eval(poly, a + dx * (i + 1));
			approx += fa*fa + fa*fb + fb*fb;
		}
		approx *= dx * slices * sin((2 * pi) / slices) / 6;
		double ratio = abs(real - approx) / real;
		cout << fixed << setprecision(4) << "Case " << caso << ": " << (ratio*100) << "\n";
	}
	return 0;
}