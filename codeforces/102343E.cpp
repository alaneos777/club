#include <bits/stdc++.h>
using namespace std;

const int M = 5e6;

int main(){
	int n, k;
	cin >> n >> k;
	vector<bool> isPrime(M+1, true);
	vector<int> primes;
	isPrime[0] = isPrime[1] = false;
	for(int i = 2; i <= M; ++i){
		if(isPrime[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > M) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
	vector<bool> arr(M + 1);
	for(int p : primes){
		if(p > n) break;
		for(int j = p; j <= M; j += p){
			arr[j] = true;
		}
	}
	vector<int> ans;
	for(int i = 2; i <= M; ++i){
		if(!arr[i] && !isPrime[i]) ans.push_back(i);
	}
	assert(k < ans.size());
	cout << ans[k - 1] << "\n";
	return 0;
}