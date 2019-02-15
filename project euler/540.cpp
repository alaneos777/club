#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using triple = tuple<lli, lli, lli>;

triple A(triple t){
	lli a, b, c;
	tie(a, b, c) = t;
	return {a - 2*b + 2*c, 2*a - b + 2*c, 2*a - 2*b + 3*c};
}

triple B(triple t){
	lli a, b, c;
	tie(a, b, c) = t;
	return {-a + 2*b + 2*c, -2*a + b + 2*c, -2*a + 2*b + 3*c};
}

triple C(triple t){
	lli a, b, c;
	tie(a, b, c) = t;
	return {a + 2*b + 2*c, 2*a + b + 2*c, 2*a + 2*b + 3*c};
}

int main(){
	lli N = 1e9;
	lli ans = 0;
	triple start = {3, 4, 5};
	function<void(triple)> gen = [&](triple t){
		if(get<2>(t) <= N){
			ans++;
			gen(A(t));
			gen(B(t));
			gen(C(t));
		}
	};
	gen(start);
	cout << ans << "\n";
	return 0;
}