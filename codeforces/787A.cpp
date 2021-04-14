#include <bits/stdc++.h>
using namespace std;

int Ceil(int a, int b){
	if((a >= 0 && b > 0) || (a < 0 && b < 0)){
		if(a % b == 0) return a / b;
		else return a / b + 1;
	}else{
		return a / b;
	}
}

int extgcd(int a, int b, int& x0, int& y0){
	int r0 = a, r1 = b, ri, s0 = 1, s1 = 0, si, t0 = 0, t1 = 1, ti, q;
	while(r1){
		q = r0/r1;
		ri = r0 - r1*q, r0 = r1, r1 = ri;
		si = s0 - s1*q, s0 = s1, s1 = si;
		ti = t0 - t1*q, t0 = t1, t1 = ti;
	}
	if(r0 < 0){
		r0 = -r0, s0 = -s0, t0 = -t0;
	}
	x0 = s0, y0 = t0;
	return r0;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	// b + a*x = d + c*y , x,y>=0
	// a*x - c*y = d-b
	int x0, y0, g = extgcd(a, -c, x0, y0);
	if((d-b) % g == 0){
		// x = x0*(d-b)/g + (c/g)*k >= 0 --> k >= x0*(b-d)/c
		// y = y0*(d-b)/g + (a/g)*k >= 0 --> k >= y0*(b-d)/a
		int k = max(Ceil(x0*(b-d), c), Ceil(y0*(b-d), a));
		int x = x0*((d-b)/g) + (c/g)*k;
		int y = y0*((d-b)/g) + (a/g)*k;
		int lhs = b + a*x;
		int rhs = d + c*y;
		assert(lhs == rhs);
		cout << lhs << "\n";
	}else{
		cout << "-1\n";
	}
	return 0;
}