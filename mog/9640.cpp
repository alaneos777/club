#include <bits/stdc++.h>
using namespace std;

int f(char c){
	if(c == 'G') return 1;
	return 0;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int m, n;
	cin >> m >> n;
	int cnt_g = 0;
	vector<vector<char>> grid(m, vector<char>(n));
	vector<vector<int>> mat(m, vector<int>(n-1)), acum(m, vector<int>(n-1));
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			cin >> grid[i][j];
			if(grid[i][j] == 'G') cnt_g++;
		}
	}
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n-1; ++j){
			mat[i][j] = f(grid[i][j]) ^ f(grid[i][j+1]);
			acum[i][j] = (j ? acum[i][j-1] : 0) + mat[i][j];
		}
	}
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n-1; ++j){
			acum[i][j] += (i ? acum[i-1][j] : 0);
		}
	}
	auto can = [&](int i0, int j0, int a){
		int i1 = i0 + a;
		int j1 = j0 + a - 1;
		if(0 <= i0 && i0 < m && 0 <= i1 && i1 < m && 0 <= j0 && j0 < n-1 && 0 <= j1 && j1 < n-1){
			return acum[i1][j1] - (j0 ? acum[i1][j0-1] : 0) - (i0 ? acum[i0-1][j1] : 0) + (i0 && j0 ? acum[i0-1][j0-1] : 0) == 0;
		}else{
			return false;
		}
	};
	int s = 0;
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n-1; ++j){
			int l = 1, r = min(m-1-i, n-1-j);
			int a = -1;
			if(l > r) continue;
			if(!can(i, j, l) && !can(i, j, r)) continue;
			while(true){
				int m = (l + r) / 2;
				if(can(i, j, m)){
					if(!can(i, j, m+1)){
						a = m;
						break;
					}else{
						l = m+1;
					}
				}else{
					r = m-1;
				}
			}
			if(a != -1){
				s = max(s, a);
			}
		}
	}
	cout << (s+1)*(s+1) << "\n";
	return 0;
}