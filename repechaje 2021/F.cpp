#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int r, c, e;
	while(cin >> r >> c >> e && !(r == 0 && c == 0 && e == 0)){
		vector<vector<char>> grid(r, vector<char>(c));
		vector<vector<int>> f(r, vector<int>(c, -1));
		for(int i = 0; i < r; ++i){
			for(int j = 0; j < c; ++j){
				cin >> grid[i][j];
			}
		}
		int x = 0, y = e-1;
		bool exit = false;
		int steps = 0, loop = 0;
		f[x][y] = 0;
		while(true){
			if(grid[x][y] == 'N'){
				tie(x, y) = make_pair(x-1, y);
			}else if(grid[x][y] == 'S'){
				tie(x, y) = make_pair(x+1, y);
			}else if(grid[x][y] == 'W'){
				tie(x, y) = make_pair(x, y-1);
			}else{
				tie(x, y) = make_pair(x, y+1);
			}
			steps++;
			if(!(0 <= x && x < r && 0 <= y && y < c)){
				exit = true;
				break;
			}else{
				if(f[x][y] != -1){
					loop = steps - f[x][y];
					steps -= loop;
					exit = false;
					break;
				}else{
					f[x][y] = steps;
				}
			}
		}
		if(exit){
			cout << steps << " step(s) to exit\n";
		}else{
			cout << steps << " step(s) before a loop of " << loop << " step(s)\n";
		}
	}
	return 0;
}