#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool isPrime(lli n){
	if(n <= 1) return false;
	for(lli d = 2; d*d <= n; ++d){
		if(n % d == 0) return false;
	}
	return true;
}

const lli limit = 1e14;
vector<lli> right_strong;

void dfs(lli n, int sum){
	if(n == 0 || isPrime(n/sum)) right_strong.push_back(n);
	for(int d = 0; d <= 9; ++d){
		if(n == 0 && d == 0) continue;
		lli v = 10*n + d;
		if(v % (sum + d) == 0 && v <= limit/10) dfs(v, sum + d);
	}
}

int main(){
	dfs(0, 0);
	lli ans = 0;
	for(lli n : right_strong){
		if(n < 10) continue;
		for(int d = 1; d <= 9; d += 2){
			lli v = 10*n + d;
			if(isPrime(v)){
				ans += v;
			}
		}
	}
	cout << ans << "\n";
	return 0;
}