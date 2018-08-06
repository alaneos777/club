#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int mod = 10;

void multPoly(vector<int> & A, vector<int> & B){
	int p0 = A[0] * B[0] % mod;
	int p2 = A[1] * B[1] % mod;
	int p1 = (A[0] + A[1]) * (B[0] + B[1]) % mod - (p0 + p2);
	while(p1 < 0) p1 += mod;
	A[0] = p0 + p2, A[1] = p1 + p2;
	if(A[0] >= mod) A[0] -= mod;
	if(A[1] >= mod) A[1] -= mod;
}

void powPoly(vector<int> & P, lli n){
	vector<int> ans = {1, 0};
	while(n){
		if(n & 1) multPoly(ans, P);
		n >>= 1;
		if(n) multPoly(P, P);
	}
	P = ans;
}

int fibo(lli n){
	vector<int> P = {0, 1};
	powPoly(P, n);
	return P[1];
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	lli n;
	while(cin >> n){
		cout << fibo(n) << "\n";
	}
	return 0;
}