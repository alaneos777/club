#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli solve(lli a, lli b, lli & s, lli & t){
	lli q, r0 = a, r1 = b, ri, s0 = 1, s1 = 0, si, t0 = 0, t1 = 1, ti;
	while(r1){
		q = r0 / r1;
		ri = r0 % r1, r0 = r1, r1 = ri;
		si = s0 - s1*q, s0 = s1, s1 = si;
		ti = t0 - t1*q, t0 = t1, t1 = ti;
	}
	if(r0 < 0) s0 *= -1, t0 *= -1, r0 *= -1;
	s = s0, t = t0;
	return r0;
}

lli piso(lli a, lli b){
	if((a >= 0 && b > 0) || (a < 0 && b < 0)){
		return a / b;
	}else{
		if(a % b == 0) return a / b;
		else return a / b - 1;
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, m, a, k;
	while(cin >> n >> m >> a >> k && !(n == 0 && m == 0 && a == 0 && k == 0)){
		lli s0, t0, d, c = a + k - n;
		d = solve(m, -a, s0, t0);
		if(c % d == 0){
			lli q = c / d;
			lli x, y;
			if(a == 0 && m == 0){
				x = s0 * q;
				y = t0 * q;
			}else if(a == 0 && m > 0){
				x = s0 * q;
				y = t0 * q - m * piso(t0 * q, m);
			}else if(a > 0 && m == 0){
				x = s0 * q - a * piso(s0 * q, a);
				y = t0 * q;
			}else{
				lli k = min(piso(t0 * q, m), piso(s0 * q, a));
				x = s0 * q - a * k;
				y = t0 * q - m * k;
			}
			if(x >= 0 && y >= 0){
				cout << n + m * x << "\n";
			}else{
				cout << "Impossible\n";
			}
		}else{
			cout << "Impossible\n";
		}
	}
	return 0;
}