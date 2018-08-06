#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int mod = 1e9 + 7;

void multPoly(vector<int> & A, vector<int> & B){
	int p0 = A[0] * 1ll * B[0] % mod;
	int p2 = A[1] * 1ll * B[1] % mod;
	int p1 = (A[0] + A[1]) * 1ll * (B[0] + B[1]) % mod - (p0 + p2);
	while(p1 < 0) p1 += mod;
	A[0] = p0 + p2, A[1] = p1 + p2;
	if(A[0] >= mod) A[0] -= mod;
	if(A[1] >= mod) A[1] -= mod;
}

void powPoly(vector<int> & P, int n){
	vector<int> ans = {1, 0};
	while(n){
		if(n & 1) multPoly(ans, P);
		n >>= 1;
		if(n) multPoly(P, P);
	}
	P = ans;
}

int fibo(int n){
	vector<int> P = {0, 1};
	powPoly(P, n);
	return P[1];
}

int main(){
	int t, n, m, ans;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &m);
		ans = fibo(m + 2) - fibo(n + 1);
		if(ans < 0) ans += mod;
		printf("%d\n", ans);
	}
	return 0;
}