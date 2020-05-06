#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli M = 1e17;
const int Mr = sqrt(2*M);

lli ans = 0;

void process(lli x, lli y){
	lli z = sqrtl((x*x + y*y)/5);
	lli d2 = x*z, d1 = y*z, rhs = x*y;
	if(rhs % 2 == 1) return;
	lli a = rhs/2;
	if(a >= d2) return;
	ans += M/a;
}

void rec(lli a, lli b, lli c){
	//(a + bi)*(2+i) = 2a-b + (a+2b)i
	lli x1 = abs(2*a - b), y1 = a + 2*b;
	if(x1 > y1) swap(x1, y1);
	if(x1 % 5 > 0 && x1*y1 <= 2*M){
		process(x1, y1);
	}

	//(a + bi)*(2-i) = 2a+b + (-a+2b)i
	lli x2 = 2*a + b, y2 = abs(-a + 2*b);
	if(x2 > y2) swap(x2, y2);
	if(x2 % 5 > 0 && x2*y2 <= 2*M){
		process(x2, y2);
	}

	lli a1 = 1*a - 2*b + 2*c;
	lli b1 = 2*a - 1*b + 2*c;
	lli c1 = 2*a - 2*b + 3*c;
	if(c1 <= Mr){
		rec(a1, b1, c1);
	}
	lli a2 = -1*a + 2*b + 2*c;
	lli b2 = -2*a + 1*b + 2*c;
	lli c2 = -2*a + 2*b + 3*c;
	if(c2 <= Mr){
		rec(a2, b2, c2);
	}
	lli a3 = 1*a + 2*b + 2*c;
	lli b3 = 2*a + 1*b + 2*c;
	lli c3 = 2*a + 2*b + 3*c;
	if(c3 <= Mr){
		rec(a3, b3, c3);
	}
}

int main(){
	rec(3, 4, 5);
	cout << ans << "\n";
	return 0;
}