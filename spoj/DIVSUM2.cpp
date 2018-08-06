#include <iostream>
#include <map>
using namespace std;
typedef __int128 lli;

lli gcd(lli a, lli b){
	lli r;
	while(b != 0) r = a % b, a = b, b = r;
	return a;
}

lli powMod(lli b, lli e, lli m){
	lli ans = 1;
	b %= m;
	while(e){
		if(e & 1) ans = (ans * b) % m;
		e >>= 1;
		b = (b * b) % m;
	}
	return ans;
}

lli Pow(lli b, lli e){
	lli ans = 1;
	while(e){
		if(e & 1) ans *= b;
		e >>= 1;
		b *= b;
	}
	return ans;
}

bool isPrimeMillerRabin(lli n){
	if(n < 2) return false;
	if(n == 2) return true;
	lli d = n - 1, s = 0;
	while(!(d & 1)){
		d >>= 1;
		++s;
	}
	for(int i = 0; i < 16; ++i){
		lli a = 1 + rand() % (n - 1);
		lli m = powMod(a, d, n);
		if(m == 1 || m == n - 1) goto exit;
		for(int k = 0; k < s - 1; ++k){
			m = m * m % n;
			if(m == n - 1) goto exit;
		}
		return false;
		exit:;
	}
	return true;
}

lli factorPollardRho(lli n){
	lli a = 1 + rand() % (n - 1);
	lli b = 1 + rand() % (n - 1);
	lli x = 2, y = 2, d = 1;
	while(d == 1 || d == -1){
		x = x * (x + b) % n + a;
		y = y * (y + b) % n + a;
		y = y * (y + b) % n + a;
		d = gcd(x - y, n);
	}
	return (d < 0 ? -d : d);
}

map<lli, int> fact;
void factorizePollardRho(lli n){
	while(n > 1 && !isPrimeMillerRabin(n)){
		lli f;
		do{
			f = factorPollardRho(n);
		}while(f == n);
		n /= f;
		factorizePollardRho(f);
		for(auto & it : fact){
			while(n % it.first == 0){
				n /= it.first;
				++it.second;
			}
		}
	}
	if(n > 1) ++fact[n];
}

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

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli n;
		cin >> n;
		fact.clear();
		factorizePollardRho(n);
		lli ans = 1;
		for(auto & info : fact){
			ans *= (Pow(info.first, info.second + 1) - 1) / (info.first - 1);
		}
		cout << ans-n << "\n";
	}
	return 0;
}