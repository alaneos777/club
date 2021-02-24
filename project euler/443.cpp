#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli lp(lli n){
	for(lli p = 2; p*p <= n; ++p){
		if(n % p == 0){
			return p;
		}
	}
	return n;
}

int main(){
	lli N = 1e15;
	vector<lli> x = {20};
	while(x.back() <= N){
		x.push_back(x.back() + (lp(2*x.back() - 1) - 3) / 2 + 1);
	}
	lli ans = 2*x[x.size()-2] + N;
	cout << ans << "\n";
	return 0;
}