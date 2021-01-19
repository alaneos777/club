#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e8;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int M(int n, int k){
	int num = power(2, n-k) * (n + (k-1) * (power(2, n) - 1) % mod) % mod;
	int den = power(2, n) - 1;
	den = (lli)den * den % mod;
	return (lli)num * den % mod;
}

int main(){
	int k = 1e4 + 7, n = 1e8 + 7;
	cout << M(n, k) << "\n";
	return 0;
}