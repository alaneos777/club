#include <iostream>
#include <vector>
using namespace std;
using lli = int64_t;
const int M = 5e5;

auto divsSieve(int n){
	vector<vector<int>> divs(n+1);
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

const auto divs = divsSieve(M);
const auto mu = muSieve(M);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, t;
	cin >> n >> t;
	vector<int> ids(n);
	vector<bool> is(n);
	for(int & id : ids) cin >> id;
	vector<int> cnt(M+1);
	lli ans = 0;
	while(t--){
		int x;
		cin >> x; --x;
		for(int d : divs[ids[x]]){
			ans -= mu[d]*(lli)cnt[d]*(cnt[d]-1)/2;
			if(is[x]) cnt[d]--;
			else cnt[d]++;
			ans += mu[d]*(lli)cnt[d]*(cnt[d]-1)/2;
		}
		is[x] = is[x] ^ 1;
		cout << ans << "\n";
	}
	return 0;
}