#include <bits/stdc++.h>
using namespace std;

int main(){
	double d, s;
	cin >> d >> s;
	double a, left = 0, right = 1e6;
	while(left < right){
		a = (left + right) / 2;
		if(abs(left - right) < 1e-10) break;
		double test = a * cosh(d / (2 * a)) - a;
		if(test < s){
			right = a;
		}else{
			left = a;
		}
	}
	double l = 2 * a * sinh(d / (2 * a));
	cout << fixed << setprecision(10) << l << "\n";
	return 0;
}