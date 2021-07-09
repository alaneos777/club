#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;
const lli inv_2 = (mod+1) / 2;
const lli inv_6 = (mod+1) / 6;

lli P(lli n, int p){
	n %= mod;
	if(p == 0) return (n+1) % mod;
	if(p == 1) return n * (n+1) % mod * inv_2 % mod;
	if(p == 2) return n * (n+1) % mod * (2*n+1) % mod * inv_6 % mod;
	return 0;
}

map<lli, int> mem_Q;
lli Q(lli n){
	if(n == 0 || n == 1) return n;
	if(mem_Q.count(n)) return mem_Q[n];
	lli m = (n-1)>>1;
	return mem_Q[n] = (Q(n/2) + Q(m) + P(m, 0)) % mod;
}

map<lli, int> mem_V;
lli V(lli n){
	if(n == 0 || n == 1) return n;
	if(mem_V.count(n)) return mem_V[n];
	lli m = (n-1)>>1;
	return mem_V[n] = (2*V(n/2) + 2*V(m) + Q(m) + 2*P(m, 1) + P(m, 0)) % mod;
}

map<lli, int> mem_R;
lli R(lli n){
	if(n == 0 || n == 1) return n;
	if(mem_R.count(n)) return mem_R[n];
	lli m = (n-1)>>1;
	return mem_R[n] = (R(n/2) + R(m) + 2*Q(m) + P(m, 0)) % mod;
}

map<lli, int> mem_U;
lli U(lli n){
	if(n == 0 || n == 1) return n;
	if(mem_U.count(n)) return mem_U[n];
	lli m = (n-1)>>1;
	return mem_U[n] = (2*U(n/2) + 2*U(m) + 4*V(m) + 2*P(m, 1) + R(m) + 2*Q(m) + P(m, 0)) % mod;
}

map<lli, int> mem_T;
lli T(lli n){
	if(n == 0 || n == 1) return n;
	if(mem_T.count(n)) return mem_T[n];
	lli m = (n-1)>>1;
	return mem_T[n] = (4*T(n/2) + 4*T(m) + 4*V(m) + Q(m) + 4*P(m, 2) + 4*P(m, 1) + P(m, 0)) % mod;
}

map<lli, int> mem_S;
lli S(lli n){
	if(n == 0 || n == 1) return n;
	if(mem_S.count(n)) return mem_S[n];
	lli m = (n-1)>>1;
	return mem_S[n] = (4*S(n/2) + 4*S(m) + 8*T(m) + 4*U(m) + 8*V(m) + R(m) + 2*Q(m) + 4*P(m, 2) + 4*P(m, 1) + P(m, 0)) % mod;
}

int main(){
	lli N = 1e16;
	cout << S(N) << "\n";
	return 0;
}