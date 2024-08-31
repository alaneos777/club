#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

map<lli, lli> mem_S, mem_T;

lli S(lli n);
lli T(lli n);

lli T(lli n){
	if(n == 0) return 0;
	if(mem_T.count(n)) return mem_T[n];
	return mem_T[n] = T(n-1) + S(3*n*n + 3*n);
}

lli S(lli n){
	if(n == 0) return 0;
	if(mem_S.count(n)) return mem_S[n];
	lli m = cbrtl(n);
	return mem_S[n] = n + T(m-1) + S(n - m*m*m);
}

int main(){
	lli N = 1e17;
	cout << S(N-1) << "\n";
	return 0;
}