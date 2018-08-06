#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 1e9 + 7;

lli inv(lli & a, lli & n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1);
		s0 = s1, s1 = si;
		ri = r0 % r1;
		r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

void multiply(lli & a1, lli & a0, lli & b1, lli & b0){
	lli c0 = (a0 * b0) % mod;
	lli c1 = ((a0 * b1) % mod + (a1 * b0) % mod) % mod;
	lli c2 = (a1 * b1) % mod;
	a1 = (c2 + c1) % mod;
	a0 = (c2 + c0) % mod;
}

void powPoly(lli & a1, lli & a0, lli n){
	lli ans0 = 1, ans1 = 0;
	lli acum0 = a0, acum1 = a1;
	while(n){
		if(n & 1) multiply(ans1, ans0, acum1, acum0);
		n >>= 1;
		multiply(acum1, acum0, acum1, acum0);
	}
	a1 = ans1, a0 = ans0;
}

lli S(lli n, lli k){
	if(n == 0) return 0;
	lli num = 0, den = 0;
	lli fk1 = 1, fk0 = 0;
	powPoly(fk1, fk0, k);
	lli fkn1 = fk1, fkn0 = fk0;
	powPoly(fkn1, fkn0, n);
	lli sq1 = 1, sq0 = 1;

	lli first1 = fk1, first0 = fk0;
	multiply(first1, first0, sq1, sq0);
	num = first1;

	lli second1 = fkn1, second0 = fkn0;
	multiply(second1, second0, first1, first0);
	num = (num - second1) % mod;

	lli third1 = fkn1, third0 = fkn0;
	multiply(third1, third0, sq1, sq0);
	if(k & 1){
		num = (num - (third1 - 1)) % mod;
	}else{
		num = (num + (third1 - 1)) % mod;
	}

	if((k & 1) == 0) den = 2;
	den = (den - fk1) % mod;
	den = (den - 2 * fk0) % mod;

	if(num < 0) num += mod;
	if(den < 0) den += mod;
	return (num * inv(den, mod)) % mod;
}

lli techo(lli a, lli b){
	lli ans = a / b;
	if(a % b > 0) ans += 1;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	lli l, r, k;
	cin >> t;
	for(int i = 1; i <= t; i++){
		cin >> l >> r >> k;
		lli ans = S(r / k, k) - S(techo(l, k) - 1, k);
		if(ans < 0) ans += mod;
		cout << "Case " << i << ": " << ans << "\n";
	}
	return 0;
}