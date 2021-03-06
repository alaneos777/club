#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct StPer{
	StPer *left, *right;
	int l, r;
	T sum;
 
	StPer(int start, int end): left(NULL), right(NULL), l(start), r(end), sum(0){
		if(l != r){
			int half = l + ((r - l) >> 1);
			left = new StPer(l, half);
			right = new StPer(half+1, r);
		}
	}

	StPer(int start, int end, T val): left(NULL), right(NULL), l(start), r(end), sum(val){}
	StPer(int start, int end, StPer* left, StPer* right): left(left), right(right), l(start), r(end){
		sum = left->sum + right->sum;
	}
 
	T sum_query(int start, int end){
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return sum;
		else return left->sum_query(start, end) + right->sum_query(start, end);
	}
 
	StPer* update(int pos, T val){
		if(l == r) return new StPer(l, r, sum + val);
		int half = l + ((r - l) >> 1);
		if(pos <= half) return new StPer(l, r, left->update(pos, val), right);
		return new StPer(l, r, left, right->update(pos, val));
	}
};

vector<vector<pair<int, int>>> generalSieve(int n){
	vector<vector<pair<int, int>>> f(n+1);
	vector<int> cnt(n+1), acum(n+1), primes;
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){ //case base: f(p)
			primes.push_back(i);
			f[i].push_back({i, 1});
			cnt[i] = 1;
			acum[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0){ //gcd(i, p) != 1
				f[d] = f[i / acum[i]];
				f[d].push_back({p, cnt[i] + 1});
				cnt[d] = cnt[i] + 1;
				acum[d] = acum[i] * p;
				break;
			}else{ //gcd(i, p) = 1
				f[d] = f[i];
				f[d].push_back({p, 1});
				cnt[d] = 1;
				acum[d] = p;
			}
		}
	}
	return f;
}

const int M = 1e6;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	auto f = generalSieve(M + 1);
	int n, ai, q, l, r, x, y;
	cin >> n;
	vector<StPer<int>*> versions(n + 1);
	versions[0] = new StPer<int>(0, M);
	for(int i = 1; i <= n; ++i){
		cin >> ai;
		StPer<int>* curr = versions[i - 1];
		for(auto & par : f[ai]){
			curr = curr->update(par.first, par.second);
		}
		versions[i] = curr;
	}
	cin >> q;
	while(q--){
		cin >> l >> r >> x >> y;
		cout << versions[r]->sum_query(x, y) - versions[l - 1]->sum_query(x, y) << "\n";
	}
	return 0;
}