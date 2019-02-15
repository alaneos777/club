#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	a %= m;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
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

const lli mod = 1234567891011ll;

inline void modula(lli & n){
	while(n >= mod) n -= mod;
}

lli fibo(lli n){
	array<lli, 2> F = {1, 0};
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	array<lli, 4> C;
	do{
		int d = (n & p) != 0;
		C[0] = C[3] = 0;
		C[d] = F[0] * F[0] % mod;
		C[d+1] = (F[0] * F[1] << 1) % mod;
		C[d+2] = F[1] * F[1] % mod;
		F[0] = C[0] + C[2] + C[3];
		F[1] = C[1] + C[2] + (C[3] << 1);
		modula(F[0]), modula(F[1]);
	}while(p >>= 1);
	return F[1];
}

int main(){
	srand(time(0));
	vector<lli> primes;
	lli i = 1e14;
	while(primes.size() < 100000){
		if(isPrimeMillerRabin(i)){
			primes.push_back(i);
		}
		i++;
	}
	lli ans = 0;
	for(lli p : primes){
		ans = (ans + fibo(p)) % mod;
	}
	cout << (long long)ans << "\n";
	return 0;
}