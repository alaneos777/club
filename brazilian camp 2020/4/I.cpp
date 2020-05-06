#include <bits/stdc++.h>
using namespace std;

vector<int> muSieve(int n){
	vector<int> Mu(n + 1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i)
		if(Mu[i])
			for(int j = 2*i; j <= n; j += i)
				Mu[j] -= Mu[i];
	return Mu;
}

const int M = 1e5;
const auto mu = muSieve(M);

vector<vector<int>> divisorsSieve(int n){
	vector<vector<int>> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			if(mu[i]) divs[j].push_back(i);
		}
	}
	return divs;
}

const auto divs = divisorsSieve(M);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	vector<vector<int>> freq(M+1);
	for(int i = 0; i < n; ++i){
		cin >> a[i];
		freq[a[i]].push_back(i);
	}
	vector<vector<int>> pos(M+1);
	for(int i = 1; i <= M; ++i){
		for(int j = i; j <= M; j += i){
			pos[i].insert(pos[i].end(), freq[j].begin(), freq[j].end());
		}
	}
	for(int i = 1; i <= M; ++i){
		sort(pos[i].begin(), pos[i].end());
	}

	auto f = [&](int x, int l, int r){
		int sum = 0;
		for(int d : divs[x]){
			sum += mu[d] * (upper_bound(pos[d].begin(), pos[d].end(), r) - lower_bound(pos[d].begin(), pos[d].end(), l));
		}
		return sum;
	};

	while(q--){
		int l, r, x;
		cin >> l >> r >> x;
		--l, --r;
		// maxima L tal que f[L,r]>=1
		int low = l, high = r;
		if(f(x, low, r) == 0 && f(x, high, r) == 0){
			cout << "-1\n";
			continue;
		}
		while(true){
			int mid = (low + high) >> 1;
			if(f(x, mid, r) >= 1){
				if(mid != r && f(x, mid+1, r) >= 1){
					low = mid+1;
				}else{
					cout << mid+1 << "\n";
					break;
				}
			}else{
				high = mid-1;
			}
		}
	}
	return 0;
}