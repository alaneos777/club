#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli SumPrimePi(lli n){
	lli v = sqrt(n), p, temp, q, j, end, i, d;
	vector<lli> lo(v+2), hi(v+2);
	vector<bool> used(v+2);
	for(p = 1; p <= v; p++){
		lo[p] = p - 1;
		hi[p] = n/p - 1;
	}
	for(p = 2; p <= v; p++){
		if(lo[p] == lo[p-1]) continue;
		temp = lo[p-1];
		q = p * p;
		hi[1] -= (hi[p] - temp);
		j = 1 + (p & 1);
		end = (v <= n/q) ? v : n/q;
		for(i = p + j; i <= 1 + end; i += j){
			if(used[i]) continue;
			d = i * p;
			if(d <= v)
				hi[i] -= (hi[d] - temp);
			else
				hi[i] -= (lo[n/d] - temp);
		}
		if(q <= v)
			for(i = q; i <= end; i += p*j)
				used[i] = true;
		for(i = v; i >= q; i--){
			lo[i] -= (lo[i/p] - temp);
		}
	}
	return hi[1];
}

vector<int> sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	is[0] = is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int j = 0; j < primes.size(); ++j){
			int p = primes[j];
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const vector<int> primes = sieve(1e8);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int q;
	cin >> q;
	while(q--){
		int n;
		cin >> n;
		if(n <= 5761455){
			cout << primes[n-1] << "\n";
		}else{
			lli l = n * logl(n), r = 1.15l * n * logl(n), ans = 1e18;
			while(r - l >= 2e6){
				lli m = (l + r) / 2;
				if(SumPrimePi(m) >= n){
					ans = m;
					r = m - 1;
				}else{
					l = m + 1;
				}
			}
			vector<bool> isPrime(r-l+1, true);
			for(int i = 0; i < primes.size(); ++i){
				lli p = primes[i];
				if(p*p > r) break;
				for(lli d = (l+p-1)/p*p; d <= r; d += p){
					isPrime[d-l] = false;
				}
			}
			lli cnt = SumPrimePi(l);
			lli i = l;
			while(cnt < n && i <= r){
				++i;
				cnt += isPrime[i-l];
			}
			if(cnt == n){
				cout << i << "\n";
			}else{
				cout << ans << "\n";
			}
		}
	}
	return 0;
}