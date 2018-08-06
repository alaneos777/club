#include <bits/stdc++.h>
using namespace std;

vector<int> lowestPrime;
void criba(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; i ++) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2){
		if(lowestPrime[i] == i){
			for(int j = i * i; j <= n; j += 2 * i){
				if(lowestPrime[j] == j) lowestPrime[j] = i;
			}
		}
	}
}

bool isSquareFree(int n){
	int primeFactors = 0;
	while(n != 1){
		int p = lowestPrime[n];
		while(n % p == 0){
			n /= p;
			primeFactors++;
			if(primeFactors > 2) return false;
		}
	}
	return primeFactors == 2;
}

int main(){
	int n = 100000000;
	int ans = 0;
	criba(n);
	for(int i = 2; i < n; i++){
		if(isSquareFree(i)) ans++;
	}
	cout << ans << "\n";
	return 0;
}