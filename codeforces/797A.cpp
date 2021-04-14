#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> primes;
	for(int p = 2; p*p <= n; ++p){
		while(n % p == 0){
			n /= p;
			primes.push_back(p);
		}
	}
	if(n > 1) primes.push_back(n);
	if(k > primes.size()){
		cout << "-1\n";
	}else{
		for(int i = 0; i < k-1; ++i){
			cout << primes[i] << " ";
		}
		int last = 1;
		for(int i = k-1; i < primes.size(); ++i){
			last *= primes[i];
		}
		cout << last << "\n";
	}
	return 0;
}