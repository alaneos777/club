#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 1e7 + 10;

vector<int> primes;
auto lpSieve(int n){
	vector<int> lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
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
	return lp;
}

const auto lp = lpSieve(M);

lli pot(lli n, lli p){
	lli ans = 0;
	while(n /= p) ans += n;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int k;
	cin >> k;
	vector<lli> a(M+1);
	lli sum = 0;
	for(int i = 0; i < k; ++i){
		int ai;
		cin >> ai;
		sum += ai;
		a[1]++;
		a[ai+1]--;
	}
	partial_sum(a.begin(), a.end(), a.begin());
	int maxi = 1;
	vector<lli> fact_den(M+1);
	for(int i = 1; i <= M; ++i){
		if(a[i] == 0) continue;
		int n = i;
		while(n > 1){
			int p = lp[n], e = 0;
			while(n % p == 0){
				n /= p;
				e++;
			}
			fact_den[p] += e*a[i];
			maxi = max(maxi, p);
		}
	}
	lli l = maxi, r = sum, n = -1;
	while(l <= r){
		lli mid = (l+r)/2;
		bool can = true;
		for(int p : primes){
			if(p > maxi) break;
			if(pot(mid, p) - fact_den[p] < 0){
				can = false;
				break;
			}
		}
		if(can){
			n = mid;
			r = mid-1;
		}else{
			l = mid+1;
		}
	}
	cout << n << "\n";
	return 0;
}