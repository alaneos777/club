#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
const lli mod = 1e9 + 7;

const int M = 1e7;

auto muSieve(int n){
	vector<int> mu(n+1, -1);
	mu[0] = mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(mu[i]){
			for(int j = 2*i; j <= n; j += i){
				mu[j] -= mu[i];
			}
		}
	}
	return mu;
}

auto lpSieve(int n){
	vector<int> lp(n+1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; ++i) lp[i] = (i&1 ? i : 2);
	for(int i = 3; i*i <= n; i += 2){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += 2*i){
				if(lp[j] == j) lp[j] = i;
			}
		}
	}
	return lp;
}

const auto mu = muSieve(M);
const auto lp = lpSieve(M);

auto getDivs(int N){
	int n = N;
	vector<pair<int, int>> f;
	while(n > 1){
		int p = lp[n], e = 0;
		while(n % p == 0){
			n /= p;
			e++;
		}
		f.emplace_back(p, e);
	}
	vector<int> divs;
	function<void(int, int)> dfs = [&](int pos, int acum){
		if(pos == f.size()){
			divs.push_back(acum);
		}else{
			int p = f[pos].first;
			dfs(pos + 1, acum);
			dfs(pos + 1, acum * p);
		}
	};
	dfs(0, 1);
	return divs;
}

void fix(lli & n){
	while(n >= mod) n -= mod;
	while(n < 0) n += mod;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> freq(M+1), freqDiv(M+1);
	vector<int> two_pow(M+1, 1);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
		freq[ai]++;
	}
	for(int d = 1; d <= M; ++d){
		for(int j = d; j <= M; j += d){
			freqDiv[d] += freq[j];
		}
		two_pow[d] = two_pow[d-1] * 2ll % mod;
	}
	lli coprime = 0;
	for(int d = 1; d <= M; ++d){
		if(mu[d]){
			coprime += mu[d] * (two_pow[freqDiv[d]] - 1);
			fix(coprime);
		}
	}
	lli ans = 0;
	for(int ai : a){
		lli subsets = coprime;
		auto divs = getDivs(ai);
		for(int d : divs){
			subsets -= mu[d] * (two_pow[freqDiv[d]] - 1);
			subsets += mu[d] * (two_pow[freqDiv[d] - 1] - 1);
			fix(subsets);
		}
		subsets = two_pow[n-1] - subsets - 1;
		fix(subsets);
		for(int d : divs){
			if(d == 1) continue;
			subsets += mu[d] * (two_pow[freqDiv[d] - 1] - 1);
			fix(subsets);
		}
		ans += subsets;
		fix(ans);
	}
	cout << ans << "\n";
	return 0;
}