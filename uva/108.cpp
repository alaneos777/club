#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<vector<int>> A(n, vector<int>(n));
	vector<vector<int>> B(n, vector<int>(n));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cin >> A[i][j];
			B[i][j] = (j == 0 ? 0 : B[i][j-1]) + A[i][j];
		}
	}
	int ans = 0;
	for(int left = 0; left < n; ++left){
		for(int right = left; right < n; ++right){
			int val = B[0][right] - (left == 0 ? 0 : B[0][left-1]);
			int ans_col = val, max_tmp = val;
			for(int row = 1; row < n; ++row){
				val = B[row][right] - (left == 0 ? 0 : B[row][left-1]);
				max_tmp = max(max_tmp + val, val);
				ans_col = max(max_tmp, ans_col);
			}
			if((left == 0 && right == 0) || ans_col > ans){
				ans = ans_col;
			}
		}
	}
	cout << ans << "\n";
	return 0;
}