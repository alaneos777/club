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

int rad(int n){
	int ans = 1;
	while(n != 1){
		int p = lowestPrime[n];
		while(n % p == 0) n /= p;
		ans *= p;
	}
	return ans;
}

int main(){
	int limit = 1e5;
	criba(limit);
	vector<pair<int, int>> table(limit + 1);
	for(int i = 1; i <= limit; i++){
		table[i] = make_pair(rad(i), i);
	}
	sort(table.begin(), table.end());
	cout << table[10000].second << "\n";
	return 0;
}