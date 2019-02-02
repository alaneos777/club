#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	b %= m;
	while(e){
		if(e & 1) ans = (ans * b) % m;
		e >>= 1;
		b = (b * b) % m;
	}
	return ans;
}

lli power(lli b, lli e){
	lli ans = 1;
	while(e){
		if(e & 1) ans = (ans * b);
		e >>= 1;
		b = (b * b);
	}
	return ans;
}

lli gcd(lli a, lli b){
	lli r;
	while(b) r = a % b, a = b, b = r;
	return a;
}

inline lli Abs(lli x){
	return x > 0 ? x : -x;
}

bool isPrime(lli n){
	if(n < 2) return false;
	if(n == 2) return true;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int i = 0; i < 16; ++i){
		lli a = 1 + rand() % (n - 1);
		lli m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) goto exit;
		for(int k = 0; k < s; ++k){
			m = m * m % n;
			if(m == n - 1) goto exit;
		}
		return false;
		exit:;
	}
	return true;
}

lli getFactor(lli n){
	lli a = 1 + rand() % (n - 1);
	lli b = 1 + rand() % (n - 1);
	lli x = 2, y = 2, d = 1;
	while(d == 1){
		x = x * (x + b) % n + a;
		y = y * (y + b) % n + a;
		y = y * (y + b) % n + a;
		d = gcd(Abs(x - y), n);
	}
	return d;
}

map<lli, int> fact;
void factorize(lli n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrime(n)){
		lli f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorize(f, false);
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

int main(){
	srand(time(0));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	long long int n;
	cin >> n;
	factorize(n);
	lli ans = 1;
	for(auto & f : fact){
		ans *= (power(f.first, f.second + 1) - 1) / (f.first - 1);
	}
	cout << ans-n << "\n";
	return 0;
}