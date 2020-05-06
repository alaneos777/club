#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

vector<int> primes;
vector<bool> isPrime;

void sieve(int n){
	isPrime.resize(n+1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
}

const int M = 1e8;

int main(){
	sieve(M);
	vector<int> pi(M+1);
	for(int i = 1; i <= M; ++i){
		pi[i] = pi[i-1] + isPrime[i];
	}
	vector<int> parent(M+1), level(M+1);
	parent[1] = 1;
	level[1] = 0;
	for(int i = 2; i <= M; ++i){
		parent[i] = pi[i];
		level[i] = level[pi[i]] + 1;
	}

	int LOG = log2(M) + 3;
	vector<vector<int>> dp(LOG, vector<int>(M+1));
	vector<vector<int>> dists(LOG, vector<int>(M+1));
	for(int u = 1; u <= M; ++u){
		dp[0][u] = parent[u];
		dists[0][u] = !isPrime[u];
	}
	for(int i = 1; (1 << i) <= M; ++i){
		for(int u = 1; u <= M; ++u){
			dp[i][u] = dp[i - 1][dp[i - 1][u]];
			dists[i][u] = dists[i - 1][u] + dists[i - 1][dp[i - 1][u]];
		}
	}

	auto sum_up_kth = [&](int u, int k){
		if(level[u] < k) return -1;
		int sum = 0;
		int m = 0;
		while(k){
			if(k & 1){
				sum += dists[m][u];
				u = dp[m][u];
			}
			m++;
			k >>= 1;
		}
		return sum + dists[0][u];
	};

	lli ans = 1;
	for(int k = 0; k <= level[M]+1; ++k){
		int cnt_k = 0;
		for(int u = 1; u <= M; ++u){
			int l = 1, r = level[u], start = -1, end = -1;
			while(l <= r){
				int m = (l + r) / 2;
				int sum = sum_up_kth(u, m);
				if(sum >= k){
					start = m;
					r = m-1;
				}else{
					l = m+1;
				}
			}
			if(start == -1) continue;
			l = 1, r = level[u];
			while(l <= r){
				int m = (l + r) / 2;
				int sum = sum_up_kth(u, m);
				if(sum <= k){
					end = m;
					l = m+1;
				}else{
					r = m-1;
				}
			}
			if(end == -1) continue;
			cnt_k += end - start + 1;
		}
		if(cnt_k) ans = ans * cnt_k % mod;
	}

	cout << ans << "\n";
	return 0;
}