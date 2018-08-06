#include <bits/stdc++.h>
using namespace std;

int main(){
	int a, b, c;
	cin >> a >> b >> c;
	double d = sqrt(b*b - 4*a*c);
	double x1 = (-b + d) / (2*a);
	double x2 = (-b - d) / (2*a);
	if(x1 < x2) swap(x1, x2);
	cout << setprecision(15) << x1 << "\n" << x2;
	return 0;
}