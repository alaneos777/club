#include <bits/stdc++.h>
using namespace std;

const int M = 1e6;

int dig_sum(int n){
	int ans = 0;
	while(n){
		ans += n%10;
		n /= 10;
	}
	return ans;
}

int digital_sum(int n){
	while(n >= 10) n = dig_sum(n);
	return n;
}

int main(){
	vector<int> dp(M);
	int ans = 0;
	for(int n = 2; n < M; ++n){
		dp[n] = digital_sum(n);
	}
	for(int d = 1; d < M; ++d){
		for(int n = d, e = 1; n < M; n += d, ++e){
			dp[n] = max(dp[n], dp[d] + dp[e]);
		}
	}
	for(int n = 2; n < M; ++n){
		ans += dp[n];
	}
	cout << ans << "\n";
	return 0;
}