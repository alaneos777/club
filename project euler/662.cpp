#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
const lli mod = 1e9 + 7;

vector<pair<int, int>> movs;

int isSq(int n){
	int l = 0, r = sqrt(1e9), ans = -1;
	while(l <= r){
		int m = (l + r) / 2;
		if(m*m <= n){
			ans = m;
			l = m+1;
		}else{
			r = m-1;
		}
	}
	if(ans*ans == n) return ans;
	else return -1;
}

int f(int w, int h){
	vector<vector<int>> dp(w+1, vector<int>(h+1));
	dp[0][0] = 1;
	for(int i = 0; i <= w; ++i){
		for(int j = 0; j <= h; ++j){
			if(i == 0 & j == 0) continue;
			for(const auto & mov : movs){
				int a, b;
				tie(a, b) = mov;
				if(i-a >= 0 && j-b >= 0){
					dp[i][j] += dp[i-a][j-b];
					if(dp[i][j] >= mod) dp[i][j] -= mod;
				}
			}
		}
	}
	return dp[w][h];
}

int main(){
	vector<int> fib = {0, 1};
	while(fib.back() <= 7000){
		fib.push_back(fib[fib.size()-1] + fib[fib.size()-2]);
	}
	for(int i = 2; i < fib.size(); ++i){
		int n = fib[i];
		for(int a = 0; a <= n; ++a){
			int b = isSq(n*n - a*a);
			if(b != -1){
				movs.emplace_back(a, b);
			}
		}
	}
	cout << f(1e4, 1e4) << "\n";
	return 0;
}