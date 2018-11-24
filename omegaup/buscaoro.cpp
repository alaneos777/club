#include <iostream>
#include <vector>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int m, n, x;
	cin >> m >> n >> x;
	vector<vector<int>> A(m, vector<int>(n));
	vector<vector<int>> B(m, vector<int>(n));
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			cin >> A[i][j];
			B[i][j] = (j == 0 ? 0 : B[i][j-1]) + A[i][j];
		}
	}
	int ans = -2e9, area = 2e9;
	for(int left = 0; left < n; ++left){
		for(int right = left; right < n; ++right){
			int curr_sum = B[0][right] - (left == 0 ? 0 : B[0][left-1]);
			int max_sum = 0;
			int start = 0;
			int i = 0, j = -1;
			for(int row = 1; row < m; ++row){
				int val = B[row][right] - (left == 0 ? 0 : B[row][left-1]);
				if(curr_sum <= x){
					if(curr_sum > max_sum){
						max_sum = curr_sum;
						i = start;
						j = row - 1;
					}else if(curr_sum == max_sum){
						if(j == -1 || (row-1 - start + 1 < j - i + 1)){
							i = start;
							j = row - 1;
						}
					}
				}
				while(curr_sum + val > x && start < m){
					curr_sum -= B[start][right] - (left == 0 ? 0 : B[start][left-1]);
					++start;
				}
				curr_sum += val;
			}
			if(curr_sum <= x){
				if(curr_sum > max_sum){
					max_sum = curr_sum;
					i = start;
					j = m - 1;
				}else if(curr_sum == max_sum){
					if(j == -1 || (m-1 - start + 1 < j - i + 1)){
						i = start;
						j = m - 1;
					}
				}
			}
			if(max_sum > ans){
				ans = max_sum;
				area = (right - left + 1) * (j - i + 1);
			}else if(max_sum == ans){
				area = min(area, (right - left + 1) * (j - i + 1));
			}
		}
	}
	cout << ans << " " << max(0, area) << "\n";
	return 0;
}