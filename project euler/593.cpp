#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<bool> is(n+1, true);
	vector<int> primes;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const int M = 1e7, sz = 1e5;
const auto primes = sieve(2e8);

struct WaveletTree{
	int lo, hi;
	WaveletTree *left, *right;
	vector<int> freq;

	WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y): lo(x), hi(y){
		if(from >= to) return;
		int m = (lo + hi) / 2;
		auto f = [m](int x){return x <= m;};
		freq.reserve(to - from + 1);
		freq.push_back(0);
		for(auto it = from; it != to; ++it){
			freq.push_back(freq.back() + f(*it));
		}
		if(hi != lo){
			auto pivot = stable_partition(from, to, f);
			left = new WaveletTree(from, pivot, lo, m);
			right = new WaveletTree(pivot, to, m + 1, hi);
		}
	}

	int kth(int l, int r, int k){
		if(l > r) return 0;
		if(lo == hi) return lo;
		int lb = freq[l - 1], rb = freq[r];
		int inLeft = rb - lb;
		if(k <= inLeft) return left->kth(lb + 1, rb, k);
		else return right->kth(l - lb, r - rb, k - inLeft);
	}
};

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	vector<int> s(M+1), s2(M+1);
	for(int k = 1; k <= M; ++k){
		s[k] = powerMod(primes[k-1], k, 10007);
	}
	for(int k = 1; k <= M; ++k){
		s2[k] = s[k] + s[k/10000 + 1];
	}
	WaveletTree wt(s2.begin()+1, s2.end(), *min_element(s2.begin()+1, s2.end()), *max_element(s2.begin()+1, s2.end()));
	lli ans = 0;
	for(int i = 1; i <= M-sz+1; ++i){
		int l = i, r = i+sz-1;
		int len = r-l+1;
		if(len & 1){
			ans += 2*wt.kth(l, r, len/2 + 1);
		}else{
			ans += wt.kth(l, r, len/2) + wt.kth(l, r, len/2 + 1);
		}
	}
	if(ans & 1){
		cout << ans/2 << ".5\n";
	}else{
		cout << ans/2 << ".0\n";
	}
	return 0;
}