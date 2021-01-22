#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 993;

struct ST{
	ST *left, *right;
	int l, r;
	int sum, lazy;
 
	ST(int start, int end): left(NULL), right(NULL), l(start), r(end), sum(1), lazy(1){
		if(l != r){
			int half = l + ((r - l) >> 1);
			left = new ST(l, half);
			right = new ST(half+1, r);
		}
	}
 
	void propagate(int dif){
		sum = (lli)sum * dif % mod;
		if(l != r){
			left->lazy = (lli)left->lazy * dif % mod;
			right->lazy = (lli)right->lazy * dif % mod;
		}
	}
 
	int query(int start, int end){
		if(lazy != 1){
			propagate(lazy);
			lazy = 1;
		}
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return sum;
		else{
			int ans = left->query(start, end) + right->query(start, end);
			if(ans >= mod) ans -= mod;
			return ans;
		}
	}
 
	void update(int start, int end, int dif){
		if(lazy != 1){
			propagate(lazy);
			lazy = 1;
		}
		if(end < l || r < start) return;
		if(start <= l && r <= end) propagate(dif);
		else{
			left->update(start, end, dif);
			right->update(start, end, dif);
			sum = left->sum + right->sum;
			if(sum >= mod) sum -= mod;
		}
	}
};

lli inverse(lli a){
	lli r0 = a, r1 = mod, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += mod;
	return s0;
}

vector<int> primes, lp, idx;
void sieve(int n){
	lp.resize(n+1); idx.resize(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			idx[i] = primes.size();
			primes.push_back(i);
			lp[i] = i;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
}

const int N = 11111111;

int main(){
	sieve(N);
	int sz = primes.size();
	ST* st = new ST(0, sz-1);
	for(int i = 0; i < sz; ++i){
		st->update(i, i, (i+1 == sz ? N+1 : primes[i+1]) - primes[i]);
	}
	lli ans = N+1;
	for(int r = 0; r <= N; ++r){
		ans += st->query(0, sz-1);
		if(ans >= mod) ans -= mod;
		if(r == N) break;
		int num = N-r, den = r+1;
		while(num > 1){
			int p = lp[num], p_pow = 1;
			while(num % p == 0){
				num /= p;
				p_pow = (lli)p_pow * p % mod;
			}
			st->update(idx[p], sz-1, p_pow);
		}
		while(den > 1){
			int p = lp[den], p_pow = 1;
			while(den % p == 0){
				den /= p;
				p_pow = (lli)p_pow * p % mod;
			}
			st->update(idx[p], sz-1, inverse(p_pow));
		}
	}
	cout << ans << "\n";
	return 0;
}