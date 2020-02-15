#include <bits/stdc++.h>
using namespace std;

vector<int> sieve(int n){
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

const int M = 1e5;
const auto lp = sieve(M);

auto fact(int n){
	vector<pair<int, int>> f;
	while(n > 1){
		int p = lp[n];
		int cnt = 0;
		while(n % p == 0){
			n /= p;
			cnt++;
		}
		f.emplace_back(p, cnt);
	}
	return f;
}

int power(int a, int b){
	int ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	vector<set<int>> vis(n);
	vector<vector<int>> freq(M+1);
	for(int i = 0; i < n; ++i){
		cin >> a[i];
		freq[a[i]].push_back(i);
	}

	int64_t ans = 0;

	function<void(int, const vector<pair<int, int>>, int, int)> solve = [&](int pos, const vector<pair<int, int>> & f, int acum, int i){
		if(pos == f.size() + 1){
			if(acum <= M && freq[acum].size() > 0 && vis[i].count(acum) == 0){
				ans += freq[acum].size() - (upper_bound(freq[acum].begin(), freq[acum].end(), i) - freq[acum].begin());
				vis[i].insert(acum);
			}
		}else if(pos == f.size()){
			long double log1 = log10l(acum);
			for(int t = 1; ; ++t){
				if(log1 + k*log10l(t) > 5.01l) break;
				solve(pos + 1, f, acum * power(t, k), i);
			}
		}else{
			int p, a;
			tie(p, a) = f[pos];
			long double log1 = log10l(acum);
			long double logp = log10l(p);
			for(int r = (a + k - 1) / k; ; ++r){
				if(log1 + (r*k-a)*logp > 5.01l) break;
				solve(pos + 1, f, acum * power(p, r*k - a), i);
			}
		}
	};

	for(int i = 0; i < n; ++i){
		auto f = fact(a[i]);
		solve(0, f, 1, i);
	}

	cout << ans << "\n";
	return 0;
}