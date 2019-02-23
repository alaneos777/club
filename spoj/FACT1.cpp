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

lli multMod(lli a, lli b, lli m){
	lli ans = 0;
	a %= m, b %= m;
	while(b){
		if(b & 1) ans = (ans + a) % m;
		b >>= 1;
		a = (a + a) % m;
	}
	return ans;
}

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	a %= m;
	while(b){
		if(b & 1) ans = multMod(ans, a, m);
		b >>= 1;
		if(b) a = multMod(a, a, m);
	}
	return ans;
}

bool isPrimeMillerRabin(lli n){
	if(n < 2) return false;
	if(n == 2) return true;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int i = 0; i < 16; ++i){
		lli a = 1 + rand() % (n - 1);
		lli m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) goto exit;
		for(int k = 0; k < s; ++k){
			m = multMod(m, m, n);
			if(m == n - 1) goto exit;
		}
		return false;
		exit:;
	}
	return true;
}

lli gcd(lli a, lli b){
	lli r;
	while(b) r = a % b, a = b, b = r;
	return a;
}

lli getFactor(lli n){
	lli a = 1 + rand() % (n - 1);
	lli b = 1 + rand() % (n - 1);
	lli x = 2, y = 2, d = 1;
	while(d == 1){
		x = multMod(x, x + b, n) + a;
		y = multMod(y, y + b, n) + a;
		y = multMod(y, y + b, n) + a;
		d = gcd(x - y >= 0 ? x - y : y - x, n);
	}
	return d;
}

map<lli, int> fact;
void factorizePollardRho(lli n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrimeMillerRabin(n)){
		lli f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorizePollardRho(f, false);
		for(auto & it : fact){
			while(n % it.first == 0){
				n /= it.first;
				++it.second;
			}
		}
	}
	if(n > 1) ++fact[n];
}

int main(){
	srand(time(0));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n;
	while(cin >> n && n != 0){
		factorizePollardRho(n);
		for(auto & par : fact){
			cout << par.first << "^" << par.second << " ";
		}
		cout << "\n";
	}
	return 0;
}