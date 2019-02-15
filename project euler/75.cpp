#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<vector<pair<int, int>>> sieve(int n){
	vector<vector<pair<int, int>>> f(n+1);
	vector<int> cnt(n+1), acum(n+1), primes;
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){ //case base: f(p)
			primes.push_back(i);
			f[i].emplace_back(i, 1);
			cnt[i] = 1;
			acum[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0){ //gcd(i, p) != 1
				f[d] = f[i / acum[i]];
				f[d].emplace_back(p, cnt[i] + 1);
				cnt[d] = cnt[i] + 1;
				acum[d] = acum[i] * p;
				break;
			}else{ //gcd(i, p) = 1
				f[d] = f[i];
				f[d].emplace_back(p, 1);
				cnt[d] = 1;
				acum[d] = p;
			}
		}
	}
	return f;
}

const int limit = 1500000;
auto all = sieve(limit);

void dfs(lli l, int pos, lli div, int & cnt){
	if(div*div >= l*l/2) return;
	if(pos == all[l].size()){
		lli x = div, y = l*l/2/x;
		if(l < 2*x && x < l && l < 2*y && y < l){
			cnt++;
		}
	}else{
		lli p = all[l][pos].first;
		int a = all[l][pos].second * 2;
		if(p == 2) a--;
		lli pw = 1;
		for(int i = 0; i <= a; ++i){
			dfs(l, pos + 1, div * pw, cnt);
			pw *= p;
		}
	}
}

/*
a+b+c=L
a^2+b^2+c=2
(a-L)(b-L)=L²/2=xy
a=L-x , b=L-y
x < y
L/2 < x < L
L/2 < y < L
*/
int main(){
	int ans = 0;
	for(int l = 2; l <= limit; l += 2){
		int cnt = 0;
		dfs(l, 0, 1, cnt);
		if(cnt == 1){
			ans++;
		}
	}
	cout << ans << "\n";
	return 0;
}