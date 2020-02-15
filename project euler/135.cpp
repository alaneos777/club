#include <bits/stdc++.h>
using namespace std;

auto sieve(int n){
	vector<vector<int>> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j].push_back(i);
		}
	}
	return divs;
}

const int M = 1e6;
const auto divs = sieve(M);

int main(){
	int cnt = 0;
	for(int n = 1; n < M; ++n){
		int sols = 0;
		for(int a : divs[n]){
			int e = n/a;
			if((a+e)%4 != 0) continue;
			int r = (a + e) / 4;
			if(a - r <= 0) continue;
			sols++;
		}
		if(sols == 10){
			cnt++;
		}
	}
	cout << cnt << "\n";
	return 0;
}