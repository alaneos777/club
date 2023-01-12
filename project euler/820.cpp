#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

const int M = 1e7;

int main(){
	lli sum = 0;
	for(int i = 1; i <= M; ++i){
		sum += 10*powerMod(10, M-1, i)/i;
	}
	cout << sum << "\n";
	return 0;
}