#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

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
		value = (value << 3) + (value << 1) + (*pos - '0');
		++pos;
	}
	value *= sgn;
	return is;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli n, ans = 0;
		cin >> n;
		lli i = 1;
		while(i <= n){
			lli ni = n / i;
			lli u = n / ni;
			//ans += (u - (i - 1)) * ((n / i) * (n / i + 1)) / 2;
			ans += (u+i)*(u-i+1) / 2 * (n / i);
			i = u + 1;
		}
		cout << ans - n * (n + 1) / 2 << "\n";
	}
	return 0;
}