#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int m, n;
	cin >> m >> n;
	int grid[m][n], ans[m][n];
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			cin >> grid[i][j];
			ans[i][j] = 0;
		}
	}
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			if(i == 0 && j == 0)
				ans[i][j] = grid[i][j];
			else if(j == 0)
				ans[i][j] = ans[i - 1][j] + grid[i][j];
			else if(i == 0)
				ans[i][j] = ans[i][j - 1] + grid[i][j];
			else
				ans[i][j] = min(ans[i][j - 1], ans[i - 1][j]) + grid[i][j];
		}
	}
	cout << ans[m - 1][n - 1] << "\n";
	return 0;
}