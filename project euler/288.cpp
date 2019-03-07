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

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

int main(){
	int n = 1e7, p = 61, m = 10;
	vector<lli> S(n+1), T(n+1);
	S[0] = 290797;
	for(int i = 1; i <= n; ++i){
		S[i] = S[i-1] * S[i-1] % 50515093;
	}
	lli sum = 0;
	for(int i = 0; i <= n; ++i){
		T[i] = S[i] % p;
		sum += T[i];
	}
	lli P = power(p, m);
	lli p_pow = 1;
	lli ans = 0;
	for(int i = 0; i < m && i < n; ++i){
		sum -= T[i];
		ans = (ans + sum * p_pow) % P;
		p_pow = p_pow * p;
	}
	cout << ans << "\n";
	return 0;
}