#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli N = 3141592653589793ll;
const int M = sqrt(N) + 100;

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

const auto mu = muSieve(M);

lli f(lli n){
	lli cnt = 0;
	lli x = 1;
	while(1){
		lli hi = (lli)floor(sqrt(n - x*x));
		lli lo = x + 1;
		if(lo > hi) break;
		cnt += hi-lo+1;
		x++;
	}
	return cnt;
}

lli Q(lli n){
	lli cnt = 0;
	for(lli k = 1; k*k <= n; ++k){
		if(mu[k]) cnt += mu[k] * f(n / (k*k));
	}
	return cnt;
}

int main(){
	lli ans = 0;
	lli two = 1;
	int alt = 1;
	while(two <= N){
		ans += alt * Q(N / two);
		alt = -alt;
		two <<= 1;
	}
	cout << ans << "\n";
	return 0;
}