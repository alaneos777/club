#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;
const lli period = 2e9 + 16;

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
		F[0] = (C[0] + C[2] + C[3]) %mod;
		F[1] = (C[1] + C[2] + (C[3] << 1)) % mod;
	}while(p >>= 1);
	return F[1];
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string N;
	cin >> N;
	lli n = 0;
	for(char c : N){
		n = (n * 10 + (c-'0')) % period;
	}
	cout << fibo(n) << "\n";
	return 0;
}