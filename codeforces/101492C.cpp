#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto mu_sieve(int n){
	vector<int> primes, lp(n+1), mu(n+1);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
			else{
				mu[d] = -mu[i];
			}
		}
	}
	return mu;
}

const int M = 5e5;
const auto mu = mu_sieve(M);

auto divsSieve(int n){
	vector<vector<int>> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			if(mu[i]) divs[j].push_back(i);
		}
	}
	return divs;
}

const auto divs = divsSieve(M);

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

struct query{
	int l, r, index;
	int64_t ord;
	query() {}
	query(int l, int r, int index): l(l), r(r), index(index) {
		ord = gilbertOrder(l, r, 21, 0);
	}
	bool operator<(const query & q) const{
		return ord < q.ord;
	}
};

vector<bool> MO(const vector<int> & a, vector<query> & queries){
	int n = a.size();
	int M = *max_element(a.begin(), a.end());
	vector<int> freq(M+1);
	vector<bool> ans(queries.size());
	sort(queries.begin(), queries.end());
	uint32_t sum = 0;
	int prevL = 0, prevR = -1;
	int i, j;
	for(const query & q : queries){
		for(i = prevL, j = min(prevR, q.l - 1); i <= j; ++i){
			//remove from the left
			for(int d : divs[a[i]]){
				if(mu[d] == 1){
					sum += (1 - freq[d] - freq[d]);
				}else{
					sum -= (1 - freq[d] - freq[d]);
				}
				freq[d]--;
			}
		}
		for(i = prevL - 1; i >= q.l; --i){
			//add to the left
			for(int d : divs[a[i]]){
				if(mu[d] == 1){
					sum += (1 + freq[d] + freq[d]);
				}else{
					sum -= (1 + freq[d] + freq[d]);
				}
				freq[d]++;
			}
		}
		for(i = max(prevR + 1, q.l); i <= q.r; ++i){
			//add to the right
			for(int d : divs[a[i]]){
				if(mu[d] == 1){
					sum += (1 + freq[d] + freq[d]);
				}else{
					sum -= (1 + freq[d] + freq[d]);
				}
				freq[d]++;
			}
		}
		for(i = prevR; i >= q.r + 1; --i){
			//remove from the right
			for(int d : divs[a[i]]){
				if(mu[d] == 1){
					sum += (1 - freq[d] - freq[d]);
				}else{
					sum -= (1 - freq[d] - freq[d]);
				}
				freq[d]--;
			}
		}
		prevL = q.l, prevR = q.r;
		ans[q.index] = (sum != 0);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	vector<query> queries(m);
	for(int i = 0; i < m; ++i){
		int l, r;
		cin >> l >> r;
		queries[i] = {l-1, r-1, i};
	}
	for(bool ans : MO(a, queries)){
		if(ans) cout << "S\n";
		else cout << "N\n";
	}
	return 0;
}