#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 100;

lli mem[M][2][2];

lli dp(lli n, int a, int b){
	if(n <= 2) return 1;
	if(mem[n][a][b] != -1) return mem[n][a][b];
	lli ans = 0;
	for(int i = 0; i < 2; ++i){
		if(!(i == 0 && a == 0 && b == 0)){
			ans += dp(n-1, i, a);
		}
	}
	return mem[n][a][b] = ans;
}

lli cnt(lli n){
	if(n == 0) return 1;
	if(n == 1) return 2;
	lli ans = 0;
	for(int i = 0; i < 2; ++i){
		for(int j = 0; j < 2; ++j){
			ans += dp(n, i, j);
		}
	}
	return ans;
}

lli getAns(lli n){
	lli ans = cnt(n);
	for(int i = 0; i < n; ++i){
		ans += cnt(i) * cnt(n-1 - i);
	}
	return ans;
}

int main(){
	memset(mem, -1, sizeof(mem));
	cout << getAns(30) << "\n";
	return 0;
}