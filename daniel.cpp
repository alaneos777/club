#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto phiSieve(int n){
	vector<lli> phi(n+1);
	iota(phi.begin(), phi.end(), 0);
	for(int i = 2; i <= n; ++i){
		if(phi[i] == i){
			for(int j = i; j <= n; j += i){
				phi[j] -= phi[j] / i;
			}
		}
	}
	return phi;
}

const int M = 2e6;
auto phi = phiSieve(M);

int main(){
	for(int i = 1; i <= M; ++i){
		phi[i]--;
	}
	vector<lli> sum;
	partial_sum(phi.begin(), phi.end(), back_inserter(sum));
	lli k;
	cin >> k;
	int n = lower_bound(sum.begin(), sum.end(), k) - sum.begin();
	k = k - sum[n-1];
	int num = -1;
	for(int i = 2; i < n; ++i){
		if(__gcd(i, n) == 1){
			k--;
			if(k == 0){
				num = i;
				break;
			}
		}
	}
	cout << num << " " << n << "\n";
	return 0;
}