#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
using pii = pair<int, int>;

const int M = 15;
vector<lli> fact(M+1, 1);

vector<int> gen_single(const vector<int> & pi){
	int n = pi.size();
	vector<bool> vis(n);
	vector<int> cnt(n+1);
	for(int i = 0; i < n; ++i){
		if(!vis[i]){
			int u = i;
			int len = 0;
			do{
				vis[u] = true;
				u = pi[u];
				len++;
			}while(u != i);
			cnt[len]++;
		}
	}
	return cnt;
}

map<vector<int>, lli> gen_all(int n){
	vector<int> pi(n);
	iota(pi.begin(), pi.end(), 0);
	map<vector<int>, lli> ans;
	do{
		ans[gen_single(pi)]++;
	}while(next_permutation(pi.begin(), pi.end()));
	return ans;
}

int lcm(int a, int b){
	return a / __gcd(a, b) * b;
}

map<vector<int>, lli> comb(int n, int m){
	map<vector<int>, lli> ans;
	for(const auto & a : gen_all(n)){
		for(const auto & b : gen_all(m)){
			vector<int> cnt(n*m+1);
			for(int p = 1; p <= n; ++p){
				for(int x = 1; x <= m; ++x){
					int q = a.first[p], y = b.first[x];
					cnt[lcm(p, x)] += q*y*__gcd(p, x);
				}
			}
			ans[cnt] += a.second*b.second;
		}
	}
	return ans;
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

int main(){
	for(int i = 1; i <= M; ++i){
		fact[i] = i * fact[i-1];
	}
	int n, m;
	lli k;
	cin >> n >> m >> k;
	lli ans = 0;
	for(auto tmp : comb(n, m)){
		/*cout << tmp.second;
		for(int i = 1; i <= n*m; ++i){
			if(tmp.first[i]) cout << " * a_" << i << "^" << tmp.first[i];
		}
		cout << "\n";*/
		ans += tmp.second * power(k, accumulate(tmp.first.begin(), tmp.first.end(), 0));
	}
	ans /= fact[n] * fact[m];
	cout << ans << "\n";
	return 0;
}

/*
3 5
48 * a_15^1
72 * a_5^1 * a_10^1
24 * a_5^3
60 * a_3^1 * a_12^1
30 * a_3^1 * a_6^2
60 * a_3^3 * a_6^1
42 * a_3^5
60 * a_2^3 * a_3^1 * a_6^1
20 * a_2^3 * a_3^3
90 * a_1^1 * a_2^1 * a_4^3
45 * a_1^1 * a_2^7
60 * a_1^2 * a_2^2 * a_3^1 * a_6^1
30 * a_1^3 * a_4^3
45 * a_1^3 * a_2^6
3 * a_1^5 * a_2^5
20 * a_1^6 * a_3^3
10 * a_1^9 * a_2^3
1 * a_1^15
*/