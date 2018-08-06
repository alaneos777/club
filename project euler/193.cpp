#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

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

int mu(int n){
	int ans = 1;
	while(n != 1){
		int p = lowestPrime[n];
		int pot = 0;
		while(n % p == 0){
			n /= p;
			pot++;
			if(pot == 2) return 0;
		}
		ans *= -1;
	}
	return ans;
}

int main(){
	lli limit = 1 << 25;
	lli N = limit * limit;
	criba(limit);
	lli count = 0;
	for(lli i = 1; i <= limit; i++){
		count += mu(i) * N / (i * i);
	}
	cout << count << "\n";
	return 0;
}