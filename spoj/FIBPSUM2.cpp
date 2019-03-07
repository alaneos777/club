#include <iostream>
#include <array>
#include <vector>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;
 
lli power(lli a, lli b){
	lli ans = 1;
	a %= mod;
	b %= mod-1;
	if(b < 0) b += mod-1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}
 
const lli inv2 = power(2, -1);
 
inline lli modula(lli n){
	while(n >= mod) n -= mod;
	while(n < 0) n += mod;
	return n;
}
 
array<lli, 2> mult(const array<lli, 2> & P, const array<lli, 2> & Q){
	lli c0 = P[0] * Q[0] % mod;
	lli c1 = modula(P[0]*Q[1]%mod + P[1]*Q[0]%mod);
	lli c2 = P[1] * Q[1] % mod;
	return {modula(c0+c2), modula(c1+c2)};
}
 
array<lli, 2> div(const array<lli, 2> & P, const array<lli, 2> & Q){
	lli d = power(modula(Q[0] * (Q[0] + Q[1]) % mod - Q[1] * Q[1] % mod), -1);
	return {modula(P[0] * (Q[0] + Q[1]) % mod - P[1] * Q[1] % mod) * d % mod, modula(P[1] * Q[0] % mod - P[0] * Q[1] % mod) * d % mod};
}
 
array<lli, 2> rec(array<lli, 2> P, lli n){
	array<lli, 2> ans = {1, 0};
	while(n){
		if(n & 1) ans = mult(ans, P);
		n >>= 1;
		P = mult(P, P);
	}
	return ans;
}
 
struct number{
	lli x, y;
	number(): x(0), y(0){}
	number(lli x, lli y): x(x), y(y){}
	number(lli n): x(n), y(0){}
	
	number operator+(const number & n) const{return number(modula(x+n.x), modula(y+n.y));}
	
	number operator-(const number & n) const{return number(modula(x-n.x), modula(y-n.y));}
	
	number operator*(const number & n) const{
		return number(modula(x*n.x%mod + 5*y*n.y%mod), modula(x*n.y%mod + y*n.x%mod));
	}
	
	number operator/(const number & n) const{
		lli den = power(modula(n.x*n.x%mod - 5*n.y*n.y%mod), -1);
		return number(modula(x*n.x%mod - 5*y*n.y%mod)*den%mod, modula(-x*n.y%mod + y*n.x%mod)*den%mod);
	}
	
	bool operator==(const number & n) const{
		return x == n.x && y == n.y;
	}
};
 
const int M = 1e5+10;
 
int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<lli> inv(M+1, 1);
	for(lli i = 2; i <= M; ++i){
		inv[i] = mod - (mod/i) * inv[mod%i] % mod;
	}
	int t, caso = 1;
	cin >> t;
	while(t--){
		lli n, c; int k;
		cin >> n >> c >> k;
		auto P = rec({0, 1}, c);
		auto P_n = rec(P, n+1);
		number ans = 0;
		lli comb = 1, alt = (k & 1) ? -1 : 1;
		array<lli, 2> A = {1, 0}, B = rec(P, k);
		array<lli, 2> A_n = {1, 0}, B_n = rec(P_n, k);
		array<lli, 2> P_inv = div({1, 0}, P), P_n_inv = div({1, 0}, P_n);
		for(int j = 0; j <= k; ++j){
			number a(modula(A[1]*inv2%mod + A[0]), A[1]*inv2%mod);
			number b(modula(B[1]*inv2%mod + B[0]), modula(-B[1]*inv2%mod));
			number prod = a*b;
			a = number(modula(A_n[1]*inv2%mod + A_n[0]), A_n[1]*inv2%mod);
			b = number(modula(B_n[1]*inv2%mod + B_n[0]), modula(-B_n[1]*inv2%mod));
			number prod_n = a*b;
			if(prod == 1)
				ans = ans + (comb*alt) * ((n+1)%mod) % mod;
			else
				ans = ans + ((prod_n - 1) / (prod - 1)) * (comb*alt);
			alt = -alt;
			comb = comb * (k - j) % mod * inv[j + 1] % mod;
			A = mult(A, P), B = mult(B, P_inv);
			A_n = mult(A_n, P_n), B_n = mult(B_n, P_n_inv);
		}
		number d;
		lli den = power(5, k/2);
		if(k & 1) d = number(0, den);
		else d = number(den, 0);
		ans = ans / d;
		cout << "Case " << caso++ << ": " << ans.x << "\n";
	}
	return 0;
}  