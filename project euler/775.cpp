#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;
const lli mod = 1e9 + 7;

ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

// https://oeis.org/A193416

const lli N = 1e16;

lli P0(lli l, lli r){
	return max(lli(0), r - l + 1);
}

lli s(lli n){
	lli lhs = 3 + 10*n + 18*n*n + 8*n*n*n;
	lli rhs = 3 + 6*n;
	if(n&1) return (lhs+rhs)/48;
	else return (lhs-rhs)/48;
}

lli sum(lli l, lli r){
	if(l > r) return 0;
	lli full = lli(ceill(2*sqrtl(r-l+1)))-2;
	lli ans = s(full);
	ans += (full+1) * (r-l+1 - (full+1)*(full+1)/4);
	return ans;
}

int main(){
	lli ans = 3*(N+4)*(N-1);

	lli i = 2;
	while(i <= N){
		lli a = cbrtl(i-1);
		lli u = min((a+1)*(a+1)*(a+1), lli(N));

		ans -= 6*a*a * P0(i, u);

		ans -= 4 * P0(a*a*a + 1, min(u, a*a*a + a*a));
		ans -= 8 * P0(a*a*a + a*a + 1, min(u, a*a*a + 2*a*a + a));
		ans -= 12 * P0(a*a*a + 2*a*a + a + 1, min(u, a*a*a + 3*a*a + 3*a + 1));

		ans -= 2 * sum(a*a*a + 1, min(u, a*a*a + a*a - 1));
		ans -= 2*(2*a-1) * P0(a*a*a + a*a, min(u, a*a*a + 3*a*a + 3*a + 1));

		ans -= 2 * P0(a*a*a + 1, min(u, a*a*a + a*a));
		ans -= 2 * sum(a*a*a + a*a + 1, min(u, a*a*a + 2*a*a + a - 1));
		ans -= 4*a * P0(a*a*a + 2*a*a + a, min(u, a*a*a + 3*a*a + 3*a + 1));

		ans -= 2 * P0(a*a*a + 1, min(u, a*a*a + 2*a*a + a));
		ans -= 2 * sum(a*a*a + 2*a*a + a + 1, min(u, a*a*a + 3*a*a + 3*a + 1));

		i = u+1;
	}
	
	cout << ans << "\n";
	cout << ans%mod << "\n";
	
	return 0;
}