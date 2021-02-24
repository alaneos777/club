#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]){
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const lli L = 1e12;
const auto primes = sieve(sqrtl(L));

map<lli, lli> mem;
lli cnt_sq_free(lli n, int idx = 0){
	if(idx == 0 && mem.count(n)) return mem[n];
	lli ans = n;
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		lli curr = n / (p * p);
		if(!curr) break;
		ans -= cnt_sq_free(curr, i+1);
	}
	if(idx == 0) mem[n] = ans;
	return ans;
}

lli sum_sq_free(lli l, lli r, lli m){
	lli ans = 0;
	lli i = l;
	while(i <= r){
		lli u = m / (m / i);
		ans += m/i * (cnt_sq_free(min(u, r)) - cnt_sq_free(i-1));
		i = u+1;
	}
	return ans;
}

int main(){
	lli ans = 0;
	for(lli s = 1; s*s <= L; ++s){
		// inc = (s-1)*#sq_free[L/(s(2s-1))] + Sum[L/(st) - s, L/(s(2s-1))+1 <= t <= L/s²]
		// inc = (2s-1)*#sq_free[L/(s(2s-1))] - s*#sq_free[L/s²] + Sum[L/(st), L/(s(2s-1))+1 <= t <= L/s²]
		ans += (2*s-1) * cnt_sq_free(L / (s * (2*s-1)));
		ans -= s * cnt_sq_free(L / (s*s));
		ans += sum_sq_free(L / (s * (2*s-1)) + 1, L / (s*s), L/s);
	}
	cout << ans << "\n";
	return 0;
}

/*
(x-n)(y-n) = n² = ab

x=a+n <= 2n
y=b+n >= 2n

a+n < b+n <= L
a<b

n+1 <= b <= L-n

2n+1 <= L

count number of pairs (b,n) such that:
 b|n²
 n+1 <= b <= L-n
 n <= (L-1)/2

Let:
 b=s²t
 n=kst
where t is square-free and maximum possible, and k is some positive integer

Then, the conditions transform to:
 kst+1 <= s²t <= L-kst
 kst <= (L-1)/2

So, we get:
 k <= (s²t-1)/(st)
 k <= (L-s²t)/(st)
 k <= (L-1)/(2st)  //this is redundant

After simplifying:
 k <= min(s-1, floor(L/(s*t))-s)

We see that s-1 <= floor(L/(s*t))-s for t <= L/(s(2s-1))
*/