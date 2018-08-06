#include <bits/stdc++.h>
using namespace std;

vector<int> primes;
vector<bool> isPrime;
void primesSieve(int n){
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
	for(int i = 4; i <= n; i += 2){
		isPrime[i] = false;
	}
	for(int i = 3; i <= n; i += 2){
		if(isPrime[i]){
			primes.push_back(i);
			for(int j = i * i; j <= n; j += 2 * i){
				isPrime[j] = false;
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	primesSieve(1139);
	vector<vector<int>> dp(1140, vector<int>(16));
	dp[0][0] = 1;
	for(int & prime : primes){
		for(int j = 1139; j >= prime; --j){
			for(int k = 15; k >= 1; --k){
				dp[j][k] += dp[j - prime][k - 1];
			}
		}
	}
	int n, k;
	while(cin >> n >> k && n && k){
		cout << dp[n][k] << "\n";
	}
	return 0;
}