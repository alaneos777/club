#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 1e9 + 7;

inline void modula(lli & n){
	if(n < 0) n += mod;
	if(n >= mod) n -= mod;
}

array<lli, 2> mult(array<lli, 2> & A, array<lli, 2> & B){
	array<lli, 2> C;
	C[0] = A[0] * B[0] % mod;
	lli C2 = A[1] * B[1] % mod;
	C[1] = (A[0] + A[1]) * (B[0] + B[1]) % mod - (C[0] + C2);
	C[0] += C2;
	C[1] += C2;
	modula(C[0]), modula(C[1]);
	return C;
}

array<lli, 2> fibo(lli n){
	array<lli, 2> ans = {1, 0}, tmp = {0, 1};
	while(n){
		if(n & 1) ans = mult(ans, tmp);
		n >>= 1;
		if(n) tmp = mult(tmp, tmp);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	lli inv = 4e8+3;
	while(t--){
		lli n;
		cin >> n;
		auto tmp = fibo(n << 2);
		lli ans = (tmp[0] + 3*tmp[1] - 1) * inv % mod;
		modula(ans);
		cout << ans << "\n";
	}
	return 0;
}