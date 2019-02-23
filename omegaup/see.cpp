#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli piso(lli a, lli b){
	if((a >= 0 && b > 0) || (a < 0 && b < 0)){
		return a / b;
	}else{
		if(a % b == 0) return a / b;
		else return a / b - 1;
	}
}

lli gcd(lli a, lli b, lli & x, lli & y){
	lli r0 = a, r1 = b, s0 = 1, s1 = 0, t0 = 0, t1 = 1, h, q;
	while(r1){
		q = r0 / r1;
		h = r0 - r1 * q, r0 = r1, r1 = h;
		h = s0 - s1 * q, s0 = s1, s1 = h;
		h = t0 - t1 * q, t0 = t1, t1 = h;
	}
	if(r0 < 0) s0 = -s0, t0 = -t0, r0 = -r0;
	x = s0, y = t0;
	return r0;
}

lli solve(lli a, lli b, lli c){
	if(a == 0 && b == 0){
		if(c == 0) return -1; //*-1
		else return 0;
	}else{
		lli x0, y0, d = gcd(a, b, x0, y0);
		//cout << "(" << a << ")(" << x0 << ") + (" << b << ")(" << y0 << ") = " << d << "\n";
		if(c % d == 0){
			if(a == 0){
				if(c/b >= 0){
					return -1; //*-1
				}else{
					return 0;
				}
			}else if(b == 0){
				if(c/a >= 0){
					return -1; //*-1
				}else{
					return 0;
				}
			}else if((a > 0) == (b > 0)){
				return max(0ll, piso(x0*c, abs(b)) + piso(y0*c, abs(a)) + 1);
			}else{
				return -1;
			}
		}else{
			return 0; //*0
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli a, b, c;
	cin >> a >> b >> c;
	lli n = solve(a, b, c);
	cout << n << "\n";
	return 0;
}