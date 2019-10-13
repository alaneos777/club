#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin >> n;
	vector<vector<char>> grid(2*n-1, vector<char>(2*n-1));
	for(int i = 0; i < 2*n-1; ++i){
		for(int j = 0; j < 2*n-1; ++j){
			cin >> grid[i][j];
		}
	}
	vector<vector<int>> M(n, vector<int>(n));
	for(int i = 0; i < 2*n-1; i += 2){
		for(int j = 0; j < 2*n-1; j += 2){
			if(grid[i][j] != '-'){
				M[i/2][j/2] = grid[i][j] - '0';
			}
		}
	}
	vector<vector<int>> mayor(n*n), menor(n*n);
	for(int i = 1; i < 2*n-1; i += 2){
		for(int j = 0; j < 2*n-1; j += 2){
			int x = (i - 1) / 2;
			int y = j / 2;
			int pos1 = x*n + y;
			int pos2 = (x+1)*n + y;
			if(grid[i][j] == 'v'){
				mayor[pos1].push_back(pos2);
				menor[pos2].push_back(pos1);
			}else if(grid[i][j] == '^'){
				mayor[pos2].push_back(pos1);
				menor[pos1].push_back(pos2);
			}
		}
	}
	for(int i = 0; i < 2*n-1; i += 2){
		for(int j = 1; j < 2*n-1; j += 2){
			int x = i / 2;
			int y = (j - 1) / 2;
			int pos1 = x*n + y;
			int pos2 = x*n + y + 1;
			if(grid[i][j] == '>'){
				mayor[pos1].push_back(pos2);
				menor[pos2].push_back(pos1);
			}else if(grid[i][j] == '<'){
				mayor[pos2].push_back(pos1);
				menor[pos1].push_back(pos2);
			}
		}
	}

	function<void(int)> rec = [&](int pos){
		if(pos == n*n){
			for(int i = 0; i < n; ++i){
				for(int j = 0; j < n; ++j){
					cout << M[i][j];
				}
				cout << "\n";
			}
			exit(0);
		}else{
			int x = pos / n;
			int y = pos % n;
			if(M[x][y] == 0){
				int lower = 0, upper = 111;
				for(int p : mayor[pos]){
					int t = M[p/n][p%n];
					if(t > 0){
						lower = max(lower, t);
					}
				}
				for(int p : menor[pos]){
					int t = M[p/n][p%n];
					if(t > 0){
						upper = min(upper, t);
					}
				}
				vector<bool> forbidden(n, false);
				for(int j = 0; j < n; ++j){
					forbidden[M[x][j]] = true;
				}
				for(int i = 0; i < n; ++i){
					forbidden[M[i][y]] = true;
				}
				for(int t = lower + 1; t <= upper - 1 && t <= n; ++t){
					if(forbidden[t]) continue;
					M[x][y] = t;
					rec(pos + 1);
					M[x][y] = 0;
				}
			}else{
				rec(pos+1);
			}
		}
	};
	rec(0);
	return 0;
}