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

lli mod = power(10, 18) + 3;

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

lli inv(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(r0 == -1) s0 *= -1;
	if(s0 < 0) s0 += m;
	return s0;
}

int M = 300;
vector<lli> fact(M+1, 1), invfact(M+1, 1), bernoulli(M+1, 1);

inline lli ncr(lli n, lli r){
	return fact[n] * invfact[r] % mod * invfact[n - r] % mod;
}

inline lli modula(lli x){
	while(x >= mod) x -= mod;
	while(x < 0) x += mod;
	return x;
}

lli S(lli n, int m){
	lli ans = 0;
	for(int k = 0; k <= m; ++k){
		ans = modula(ans + ncr(m + 1, k) * bernoulli[k] % mod * powerMod(n, m + 1 - k, mod) % mod);
	}
	ans = ans * inv(m + 1, mod) % mod;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int m; lli n;
	cin >> m >> n;

	for(int i = 1; i <= M; ++i){
		fact[i] = fact[i-1] * i % mod;
		invfact[i] = inv(fact[i], mod);
	}
	for(int n = 1; n <= M; ++n){
		for(int k = 0; k < n; ++k){
			bernoulli[n] = modula(bernoulli[n] - bernoulli[k] * ncr(n, k) % mod * inv(n - k + 1, mod) % mod);
		}
	}

	lli f = S(n, m);
	lli g = modula((n + 1) * f % mod - S(n, m + 1));
	lli h = 0;
	for(int i = 0; i <= m; ++i){
		h = modula(h + S(n, i));
	}
	cout << f << " " << g << " " << h << "\n";
	return 0;
}