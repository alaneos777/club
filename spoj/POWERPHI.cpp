#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

inline lli modula(lli x){
	while(x >= mod) x -= mod;
	while(x < 0) x += mod;
	return x;
}

array<lli, 2> mult(array<lli, 2> & A, array<lli, 2> & B){
	lli c0 = A[0] * B[0] % mod;
	lli c1 = modula(A[0] * B[1] % mod + A[1] * B[0] % mod);
	lli c2 = A[1] * B[1] % mod;
	return {modula(c0 + c2), modula(c1 + c2)};
}

lli power(array<lli, 2> A, lli b){
	array<lli, 2> ans = {1, 0};
	while(b){
		if(b & 1) ans = mult(ans, A);
		b >>= 1;
		A = mult(A, A);
	}
	return modula(ans[0] + ans[0] + ans[1]);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli n;
		cin >> n;
		if(n <= 2) cout << n+1 << "\n";
		else cout << power({0, 1}, n) << "\n";
	}
	return 0;
}