#include <bits/stdc++.h>

typedef long long int lli;

using namespace std;

void euclides(lli a, lli b, lli & mcd, lli & s, lli & t){
	lli r0 = a, r1 = b, ri, s0 = 1, s1 = 0, si, t0 = 0, t1 = 1, ti, q;
	while(r1 != 0){
		q = r0 / r1, ri = r0 % r1;
		si = s0 - s1*q, ti = t0 - t1*q;
		r0 = r1, r1 = ri;
		s0 = s1, s1 = si;
		t0 = t1, t1 = ti;
	}
	mcd = r0;
	s = s0;
	t = t0;
}

int main(){
	ios_base::sync_with_stdio(0);
	int casos;
	lli n1, f1, d1, n2, f2, d2, q, d, s0, t0, m, n, l1, l2, u1, u2;
	cin >> casos;
	for(int i = 1; i <= casos; i++){
		cin >> n1 >> f1 >> d1 >> n2 >> f2 >> d2;
		euclides(d1, d2, d, s0, t0);
		q = (f2 - f1) / d;
		m = d2 / d;
		n = d1 / d;
		l1 = ceil(-(double)s0*(double)q / (double)m);
		l2 = ceil((double)t0*(double)q / (double)n);
		u1 = floor(((double)(n1 - 1) - (double)s0*(double)q) / (double)m);
		u2 = floor(((double)(n2 - 1) + (double)t0*(double)q) / (double)n);
		cout << min(u1, u2) - max(l1, l2) + 1 << "\n";
	}
	return 0;
}