#include <bits/stdc++.h>
using namespace std;
typedef unsigned __int128 lli;

ostream &operator<<(ostream &os, const lli & value){
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

istream &operator>>(istream &is, lli & value){
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

struct fraccion{
	lli num, den;
	fraccion(){
		num = 0, den = 1;
	}
	fraccion(lli x, lli y){
		if(y < 0)
			x *= -1, y *=-1;
		lli d = __gcd(x > 0 ? x : -x, y > 0 ? y : -y);
		num = x/d, den = y/d;
	}
	fraccion(lli v){
		num = v;
		den = 1;
	}
	fraccion operator+(const fraccion& f) const{
		lli d = __gcd(den, f.den);
		return fraccion(num*(f.den/d) + f.num*(den/d), den*(f.den/d));
	}
	fraccion operator*(const fraccion& f) const{
		return fraccion(num*f.num, den*f.den);
	}
	fraccion operator/(const fraccion& f) const{
		return fraccion(num*f.den, den*f.num);
	}
	lli floor() const{
		return num / den;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli n, p, sum = 0;
		cin >> n >> p;
		fraccion l((2 * p) / (n * (n + 1))), r = l + 1, m = 0;
		for(int i = 1; i <= 17; ++i){
			m = (l + r) / 2;
			sum = 0;
			for(lli i = 1; i <= n; ++i){
				sum += (m * i).floor();
			}
			if(sum == p) break;
			else if(sum > p) r = m;
			else l = m;
		}
		if(sum == p)
			cout << m.floor() << "\n";
		else
			cout << "-1\n";
	}
	return 0;
}