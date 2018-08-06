#include <bits/stdc++.h>
using namespace std;

void comb_lineal(int a, int b, int & d, int & s, int & t){
	int r0 = a, r1 = b, ri, s0 = 1, s1 = 0, si, t0 = 0, t1 = 1, ti, q;
	while(r1 != 0){
		q = r0 / r1, ri = r0 % r1;
		si = s0 - s1*q, ti = t0 - t1*q;
		r0 = r1, r1 = ri;
		s0 = s1, s1 = si;
		t0 = t1, t1 = ti;
	}
	d = r0, s = s0, t = t0;
}

int main(){
	int a, b, c, d, s0, t0, l, u;
	cin >> a >> b >> c;
	comb_lineal(a, b, d, s0, t0);
	if(c % d == 0){
		l = ceil(-(double)(s0*c)/(double)b);
		u = floor((double)(t0*c)/(double)a);
		if(u - l + 1 > 0) cout << "Yes";
		else cout << "No";
	}else{
		cout << "No";
	}
	return 0;
}