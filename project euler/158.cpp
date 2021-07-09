#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	vector<vector<lli>> ncr(27);
	ncr[0] = {1};
	for(int i = 1; i < 27; ++i){
		ncr[i] = vector<lli>(i+1);
		ncr[i][0] = ncr[i][i] = 1;
		for(int j = 1; j < i; ++j){
			ncr[i][j] = ncr[i-1][j-1] + ncr[i-1][j];
		}
	}
	lli ans = 0;
	for(int n = 1; n <= 26; ++n){
		lli pn = ncr[26][n] * ((1ll<<n) - n - 1);
		ans = max(ans, pn);
		cout << n << ": " << pn << "\n";
	}
	cout << ans << "\n";
	return 0;
}