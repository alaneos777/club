#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a ;
		b >>= 1;
		a = a * a;
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
		d = __gcd(abs(x - y), n);
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

lli r2(lli n){
	lli ans = 1;
	factorizePollardRho(n);
	for(auto & par : fact){
		lli p; int a;
		tie(p, a) = par;
		if(p % 4 == 1){
			ans *= a + 1;
		}else if(p % 4 == 3){
			if(a % 2 == 1){
				return 0;
			}
		}
	}
	return ans;
}

lli r3odd(lli n){
	int lambda = 0;
	while(n % 9 == 0){
		n /= 9;
		lambda++;
	}
	if(lambda == 0){
		lli ans = 0;
		for(lli i = 0; i*i <= n; ++i){
			ans += r2(n - i*i);
		}
		return ans;
	}else{
		if(n % 24 == 11) return power(3, lambda) * r3odd(n);
		else if(n % 24 == 19) return (2*power(3, lambda) - 1) * r3odd(n);
		else return (power(3, lambda+1) - 1) / 2 * r3odd(n);
	}
}

int main(){
	srand(time(0));
	lli n = 17526000000000ll;
	cout << (long long int)r3odd(8*n+3) << "\n";
	return 0;
}