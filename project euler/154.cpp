#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int pot(int n, int p){
	int ans = 0;
	while(n /= p) ans += n;
	return ans;
}

int main(){
	int N = 2e5;
	vector<vector<int>> pots(2, vector<int>(N+1));
	for(int i = 0; i <= N; ++i){
		pots[0][i] = pot(i, 2);
		pots[1][i] = pot(i, 5);
	}
	lli ans = 0;
	for(int i = 0; i <= N; ++i){
		for(int j = i; 2*j <= N-i; ++j){
			int k = N-i-j;
			int v2 = pots[0][N] - pots[0][i] - pots[0][j] - pots[0][k];
			int v5 = pots[1][N] - pots[1][i] - pots[1][j] - pots[1][k];
			if(v2 >= 12 && v5 >= 12){
				if(i == j || j == k || i == k) ans += 3;
				else ans += 6;
			}
		}
	}
	cout << ans << "\n";
	return 0;
}