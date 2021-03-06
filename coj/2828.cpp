#include <iostream>
using namespace std;
typedef long long int lli;

lli mod = 1e9 + 7;

inline void modula(lli & n){
	while(n < 0) n += mod;
	while(n >= mod) n -= mod;
}

lli *mult(lli *&A, lli *&B){
	lli *C = new lli[2];
	C[0] = A[0] * B[0] % mod;
	lli C2 = A[1] * B[1] % mod;
	C[1] = (A[0] + A[1]) * (B[0] + B[1]) % mod - (C[0] + C2);
	C[0] += C2;
	C[1] += C2;
	modula(C[0]);
	modula(C[1]);
	return C;
}

lli *fibo(lli n){
	lli *ans = new lli[2]();
	lli *tmp = new lli[2]();
	ans[0] = tmp[1] = 1;
	while(n){
		if(n & 1) ans = mult(ans, tmp);
		n >>= 1;
		if(n) tmp = mult(tmp, tmp);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	lli k;
	while(cin >> k){
		lli *f = fibo(k + 3);
		lli ans = f[0] * f[0] % mod - 2 * (f[1] - 1) % mod;
		if(!(k & 1)) ++ans;
		modula(ans);
		cout << ans << "\n";
	}
	return 0;
}