#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 1e9;

inline void modula(lli & n){
	while(n < 0) n += mod;
	while(n >= mod) n -= mod;
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

lli fibo(lli n){
	array<lli, 2> ans = {1, 0}, tmp = {0, 1};
	while(n){
		if(n & 1) ans = mult(ans, tmp);
		n >>= 1;
		if(n) tmp = mult(tmp, tmp);
	}
	return ans[1];
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	lli n;
	cin >> t;
	while(t--){
		cin >> n;
		cout << setfill('0') << setw(9) << fibo(n) << "\n";
	}
	return 0;
}