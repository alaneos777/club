#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> sieve(int n){
	vector<int> gp(n + 1, 1);
	gp[0] = gp[1] = 0;
	for(int i = 2; i <= n; ++i) gp[i] = i;
	for(int i = 2; i <= n; i++)
		if(gp[i] == i)
			for(int j = i; j <= n; j += i)
				gp[j] = i;
	return gp;
}

const int M = 1e9;
const auto gp = sieve(M);

int main(){
	int cnt = 0;
	for(int i = 1; i <= M; ++i){
		if(gp[i] <= 100) cnt++;
	}
	cout << cnt << "\n";
	return 0;
}