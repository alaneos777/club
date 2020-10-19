#include <bits/stdc++.h>
using namespace std;
using ld = long double;

ld go(ld a, ld b, ld c, int n){
	if(n == 0) return 0;
	ld r = 1 / (1/a + 1/b + 1/c + 2*sqrtl(1/(a*b) + 1/(a*c) + 1/(b*c)));
	return r*r + go(a, b, r, n-1) + go(a, r, c, n-1) + go(r, b, c, n-1);
}

int main(){
	const int N = 10;
	ld R = 1 / (2*sqrt(3) - 3);
	ld ans = 3 + 3*go(1, 1, -R, N) + go(1, 1, 1, N);
	cout << fixed << setprecision(8) << 1 - ans / (R*R) << "\n";
	return 0;
}