#include <bits/stdc++.h>
using namespace std;

vector<int> lowest;

void sieve(int n){
	lowest.resize(n + 1, 1);
	lowest[0] = lowest[1] = 0;
	for(int i = 2; i <= n; ++i)
		lowest[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lowest[i] == i)
			for(int j = i * i; j <= n; j += (i << 1))
				if(lowest[j] == j) lowest[j] = i;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int upper = 5e6 + 10;
	sieve(upper);
	vector<unordered_map<int, int>> factorizations(upper + 1);
	for(int i = 2; i <= upper; ++i){
		int n = i;
		while(n != 1){
			int p = lowest[n];
			int pot = 0;
			while(n % p == 0){
				n /= p;
				++pot;
			}
			factorizations[i][p] = pot;
		}
	}
	return 0;
	int n;
	while(cin >> n && n){
		//
	}
	return 0;
}