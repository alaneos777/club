#include <bits/stdc++.h>
using namespace std;

auto sieve(int n){
	vector<int> primes; vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const int M = 1e4 + 7;
const auto primes = sieve(M);
int pre[M+1][M/3];

int pot(int n, int p){
	int ans = 0;
	while(n /= p) ans += n;
	return ans;
}

void factFactorial(int n, vector<int>& fact, int m){
	for(int i = 0; i < primes.size(); ++i){
		int p = primes[i];
		if(p > n) break;
		fact[p] += m*pre[n][i];
	}
}

bool divisible(const vector<int>& fact, int n){
	for(int i = 0; i < primes.size(); ++i){
		int p = primes[i];
		if(p > n) break;
		if(fact[p] < pre[n][i]) return false;
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	if(fopen("factorial.in", "r")){
		freopen("factorial.in", "r", stdin);
		freopen("factorial.out", "w", stdout);
	}
	for(int n = 1; n <= M; ++n){
		for(int i = 0; i < primes.size(); ++i){
			pre[n][i] = pot(n, primes[i]);
		}
	}
	int n, m;
	cin >> n >> m;
	vector<int> fact(M+1);
	for(int i = 1; i <= n; ++i){
		int pi;
		cin >> pi;
		factFactorial(pi, fact, 1);
	}
	for(int i = 1; i <= m; ++i){
		int qi;
		cin >> qi;
		factFactorial(qi, fact, -1);
	}
	for(int a : fact){
		if(a < 0){
			cout << "-1\n";
			return 0;
		}
	}
	map<int, int, greater<int>> ans;
	int prev = M;
	while(true){
		int l = 2, r = prev, curr = -1;
		while(l <= r){
			int mid = (l + r) / 2;
			if(divisible(fact, mid)){
				curr = mid;
				l = mid+1;
			}else{
				r = mid-1;
			}
		}
		if(curr == -1) break;
		for(int i = 0; i < primes.size(); ++i){
			int p = primes[i];
			if(p > curr) break;
			fact[p] -= pre[curr][i];
		}
		ans[curr]++;
		prev = curr;
	}
	cout << ans.size() << "\n";
	for(auto[f, e] : ans){
		cout << f << " " << e << "\n";
	}
	return 0;
}