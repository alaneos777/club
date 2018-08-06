#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 1e9 + 7;

void multPoly(vector<lli> & A, vector<lli> & B){
	lli p0 = A[0] * B[0] % mod;
	lli p2 = A[1] * B[1] % mod;
	lli p1 = (A[0] + A[1]) * (B[0] + B[1]) % mod - (p0 + p2);
	while(p1 < 0) p1 += mod;
	A[0] = p0 + p2, A[1] = p1 + p2;
	if(A[0] >= mod) A[0] -= mod;
	if(A[1] >= mod) A[1] -= mod;
}

void powPoly(vector<lli> & P, lli n){
	vector<lli> ans = {1, 0};
	while(n){
		if(n & 1) multPoly(ans, P);
		n >>= 1;
		if(n) multPoly(P, P);
	}
	P = ans;
}

lli fibo(lli n){
	vector<lli> P = {0, 1};
	powPoly(P, n);
	return P[1];
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	lli n;
	cin >> t;
	while(t--){
		cin >> n;
		if(n == 0) cout << "0\n";
		else if(n == 1) cout << "2\n";
		else cout << fibo(n + 3) << "\n";
	}
	return 0;
}