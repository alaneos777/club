#include <bits/stdc++.h>
using namespace std;

using state = tuple<int, int, int, int>;

int main(){
	int n = 60;

	map<state, double> dp;
	state start = {0, 0, 0, 0};
	dp[start] = 1;

	double ans = 0;

	for(int r = 4*n; r >= 0; --r){
		map<state, double> new_dp;
		for(const auto&[u, p] : dp){
			auto[m, a1, a2, a3] = u;

			if(r == 0){
				ans += m*p;
				continue;
			}

			if(r > 3*a1+2*a2+a3){
				state v0 = {max(m, a1+1+a2+a3), a1+1, a2, a3};
				new_dp[v0] += p * (1 - 1.0*(3*a1+2*a2+a3)/r);
			}

			if(a1 > 0){
				state v1 = {m, a1-1, a2+1, a3};
				new_dp[v1] += p * (3.0*a1/r);
			}

			if(a2 > 0){
				state v2 = {m, a1, a2-1, a3+1};
				new_dp[v2] += p * (2.0*a2/r);
			}

			if(a3 > 0){
				state v3 = {m, a1, a2, a3-1};
				new_dp[v3] += p * (1.0*a3/r);
			}
		}
		dp = new_dp;
	}

	cout << fixed << setprecision(8) << ans << "\n";

	return 0;
}