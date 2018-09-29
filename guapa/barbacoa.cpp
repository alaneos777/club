#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 777767777;

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
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli a, b;
		cin >> a >> b;
		lli ans = fibo(b + 2) - fibo(a + 1);
		while(ans < 0) ans += mod;
		modula(ans);
		cout << ans << "\n";
	}
	return 0;
}