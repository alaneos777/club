#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int MX = 5e5;

auto divsSieve(int n){
	vector<vector<int>> divs(n);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j].push_back(i);
		}
	}
	return divs;
}

auto muSieve(int n){
	vector<int> mu(n+1, -1);
	mu[0] = 0, mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(mu[i]){
			for(int j = 2*i; j <= n; j += i){
				mu[j] -= mu[i];
			}
		}
	}
	return mu;
}

const auto mu = muSieve(MX);
const auto divs = divsSieve(MX);

lli comb(lli r){
	return r * (r - 1) / 2;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	vector<int> cnt(MX+1);
	vector<bool> shelf(n);
	lli ans = 0;
	for(int i = 0; i < q; ++i){
		int x;
		cin >> x;
		--x;
		int ai = a[x];
		if(shelf[x]){
			shelf[x] = 0;
			for(int d : divs[ai]){
				ans -= mu[d] * comb(cnt[d]);
				cnt[d]--;
				ans += mu[d] * comb(cnt[d]);
			}
		}else{
			shelf[x] = 1;
			for(int d : divs[ai]){
				ans -= mu[d] * comb(cnt[d]);
				cnt[d]++;
				ans += mu[d] * comb(cnt[d]);
			}
		}
		cout << ans << "\n";
	}
	return 0;
}