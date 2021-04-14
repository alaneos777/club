#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli Floor(lli a, lli b){
	if((a >= 0 && b > 0) || (a < 0 && b < 0)){
		return a / b;
	}else{
		if(a % b == 0) return a / b;
		else return a / b - 1;
	}
}

lli Ceil(lli a, lli b){
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
		ri = r0 - r1 * q, r0 = r1, r1 = ri;
		si = s0 - s1 * q, s0 = s1, s1 = si;
		ti = t0 - t1 * q, t0 = t1, t1 = ti;
	}
	if(r0 < 0) r0 = -r0, s0 = -s0, t0 = -t0;
	x0 = s0, y0 = t0;
	return r0;
}

lli solve(int a, int b, int c, int x1, int x2, int y1, int y2){
	if(a == 0 && b == 0){ // 0 = c
		if(c == 0){
			return lli(x2 - x1 + 1) * (y2 - y1 + 1);
		}else{
			return 0;
		}
	}else if(a == 0 && b != 0){ // by = c
		if(c % b == 0){
			int y = c/b;
			if(y1 <= y && y <= y2){
				return x2 - x1 + 1;
			}else{
				return 0;
			}
		}else{
			return 0;
		}
	}else if(a != 0 && b == 0){ // ax = c
		if(c % a == 0){
			int x = c/a;
			if(x1 <= x && x <= x2){
				return y2 - y1 + 1;
			}else{
				return 0;
			}
		}else{
			return 0;
		}
	}else{ // ax + by = c
		int x0, y0;
		int d = extgcd(a, b, x0, y0);
		if(c % d == 0){
			/*
			q = c/d
			a*x0 + b*y0 = gcd(a,b) = d
			a*(x0*q) + b*(y0*q) = c

			x = x0*q - (b/d)*k
			y = y0*q + (a/d)*k

			x1 <= x <= x2:
			(x0*q - x2) / (b/d) <= k <= (x0*q - x1) / (b/d)

			y1 <= y <= y2:
			(y1 - y0*q) / (a/d) <= k <= (y2 - y0*q) / (a/d)
			*/
			lli q = c/d;
			lli xi, xj, yi, yj;
			if(b > 0){
				xi = Ceil(x0*q - x2, b/d), xj = Floor(x0*q - x1, b/d);
			}else{
				xi = Ceil(x0*q - x1, b/d), xj = Floor(x0*q - x2, b/d);
			}
			if(a > 0){
				yi = Ceil(y1 - y0*q, a/d), yj = Floor(y2 - y0*q, a/d);
			}else{
				yi = Ceil(y2 - y0*q, a/d), yj = Floor(y1 - y0*q, a/d);
			}
			lli L = max(xi, yi), R = min(xj, yj);
			return max(0ll, R - L + 1);
		}else{
			return 0;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		int a, b, c, x1, x2, y1, y2;
		cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
		c = -c;
		cout << "Case " << caso << ": " << solve(a, b, c, x1, x2, y1, y2) << "\n";
	}
	return 0;
}