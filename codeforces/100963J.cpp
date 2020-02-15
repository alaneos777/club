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
		lli x0, y0;
		lli d = solve(m, -a, x0, y0);
		if((k - n) % d == 0){
			lli q = (k - n) / d;
			lli t = min(piso(x0*(k-n), a), piso(y0*(k-n)-d, m));
			lli x = x0*q - (a/d)*t;
			lli y = y0*q - (m/d)*t;
			lli ans = n + m*x;
			assert(ans == k + a*y);
			cout << ans << "\n";
		}else{
			cout << "Impossible\n";
		}
	}
	return 0;
}