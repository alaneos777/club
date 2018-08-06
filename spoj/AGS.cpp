#include <bits/stdc++.h>
using namespace std;
typedef __int128 lli;

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

istream &operator>>(istream &is, __int128 & value){
	char buffer[64];
	is >> buffer;
	char *pos = begin(buffer);
	int sgn = 1;
	value = 0;
	if(*pos == '-'){
		sgn = -1;
		++pos;
	}else if(*pos == '+'){
		++pos;
	}
	while(*pos != '\0'){
		value = value * 10 + (*pos - '0');
		++pos;
	}
	value *= sgn;
	return is;
}

lli expBin(lli a, lli b, lli m){
	a %= m;
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli a, d, r, n, m;
		cin >> a >> d >> r >> n >> m;
		lli p = (n - 1) / 2;
		lli M = m * (r - 1);
		lli g;
		if(r == 1) g = p % m;
		else g = (expBin(r, p + 1, M) - r) / (r - 1) % m;
		if(g < 0) g += m;
		lli ans = a * expBin(r, p, m) + g * d;
		if(n % 2 == 0) ans += d;
		ans %= m;
		cout << ans << "\n";
	}
	return 0;
}