#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m = 2;
	cin >> n;
	vector<vector<lli>> grid(m+1, vector<lli>(n+1));
	vector<lli> zigzag(n+2), pre1(n+2), pre2(n+2), suf1(n+2), suf2(n+2), acum1(n+2), acum2(n+2);
	for(int i = 1; i <= m; ++i){
		for(int j = 1; j <= n; ++j){
			cin >> grid[i][j];
		}
	}
	for(int j = 1; j <= n; ++j){
		acum1[j] = acum1[j-1] + grid[1][j];
		acum2[j] = acum2[j-1] + grid[2][j];
		pre1[j] = pre1[j - 1] + (j-1) * grid[1][j];
		pre2[j] = pre2[j - 1] + (j-1) * grid[2][j];
		if(j & 1)
			zigzag[j] = zigzag[j - 1] + (2*j - 2) * grid[1][j] + (2*j - 1) * grid[2][j];
		else
			zigzag[j] = zigzag[j - 1] + (2*j - 1) * grid[1][j] + (2*j - 2) * grid[2][j];
	}
	for(int j = n; j >= 1; --j){
		suf1[j] = suf1[j+1] + (n-j) * grid[1][j];
		suf2[j] = suf2[j+1] + (n-j) * grid[2][j];
	}
	lli ans = 0;
	for(int i = 0; i <= n; ++i){
		if(i & 1)
			ans = max(ans, zigzag[i] + (pre2[n] - pre2[i] + i * (acum2[n] - acum2[i])) + (suf1[i+1] + (n+i) * (acum1[n] - acum1[i])));
		else
			ans = max(ans, zigzag[i] + (pre1[n] - pre1[i] + i * (acum1[n] - acum1[i])) + (suf2[i+1] + (n+i) * (acum2[n] - acum2[i])));
	}
	cout << ans << "\n";
	return 0;
}