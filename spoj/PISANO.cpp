#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline lli modula(lli n, lli mod){
	while(n >= mod) n -= mod;
	while(n < 0) n += mod;
	return n;
}

array<lli, 2> fibo(lli n, lli mod){
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
		F[0] = modula(C[0] + C[2] + C[3], mod);
		F[1] = modula(C[1] + C[2] + (C[3] << 1), mod);
	}while(p >>= 1);
	return {F[0], F[1]};
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

lli powerMod(lli a, lli b, lli mod){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans % mod;
}

lli gcd(lli a, lli b){
	lli r;
	while(b) r = a%b, a = b, b = r;
	return a;
}

lli lcm(lli a, lli b){
	return a * (b / gcd(a, b));
}

lli aleatorio(lli a, lli b){
	std::uniform_int_distribution<lli> dist(a, b);
	return dist(rng);
}

bool isPrime(lli n){
	if(n < 2) return false;
	if(n == 2) return true;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int i = 0; i < 32; ++i){
		lli a = aleatorio(1, n-1);
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
	lli a = aleatorio(1, n-1);
	lli b = aleatorio(1, n-1);
	lli x = 2, y = 2, d = 1;
	while(d == 1){
		x = x * (x + b) % n + a;
		y = y * (y + b) % n + a;
		y = y * (y + b) % n + a;
		d = gcd(x-y > 0 ? x-y : y-x, n);
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

lli period_prime(lli p){
	if(p == 2) return 3;
	if(p == 5) return 20;
	if(p%10 == 1 || p%10 == 9){
		lli order = p - 1;
		factorize(order);
		for(auto par : fact){
			lli q; int a;
			tie(q, a) = par;
			order /= power(q, a);
			auto tmp = fibo(order+1, p);
			while(!(tmp[0] == 0 && tmp[1] == 1)){
				order *= q;
				tmp = fibo(order+1, p);
			}
		}
		return order;
	}
	if(p%10 == 3 || p%10 == 7){
		lli order = 2*p + 2;
		factorize(order);
		for(auto par : fact){
			lli q; int a;
			tie(q, a) = par;
			order /= power(q, a);
			auto tmp = fibo(order+1, p);
			while(!(tmp[0] == 0 && tmp[1] == 1)){
				order *= q;
				tmp = fibo(order+1, p);
			}
		}
		return order;
	}
}

lli period(lli mod){
	factorize(mod);
	lli ans = 1;
	auto f = fact;
	for(auto par : f){
		lli p; int a;
		tie(p, a) = par;
		ans = lcm(ans, power(p, a-1) * period_prime(p));
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		long long int mod;
		cin >> mod;
		cout << (long long int)period(mod) << "\n";
	}
	return 0;
}