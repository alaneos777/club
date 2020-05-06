#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli lcm(lli a, lli b){
	return a / __gcd(a, b) * b;
}

const int M = 31;
vector<lli> lcms(M+2, 1);

lli P(int s, lli N){
	return (N - 2) / lcms[s] - (N - 2) / lcms[s+1];
}

int main(){
	for(int i = 2; i <= M+1; ++i){
		lcms[i] = lcm(lcms[i-1], i);
	}
	lli ans = 0;
	for(int i = 1; i <= M; ++i){
		ans += P(i, 1ll << (2*i));
	}
	cout << ans << "\n";
	return 0;
}