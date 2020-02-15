#include <bits/stdc++.h>
using namespace std;

char grid[9][9];

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			cin >> grid[i][j];
		}
	}
	int x, y;
	cin >> x >> y;
	--x, --y;
	x %= 3, y %= 3;
	int a = x*3, b = a+2, c = y*3, d = c+2;
	bool found = false;
	for(int i = a; i <= b; ++i){
		for(int j = c; j <= d; ++j){
			if(grid[i][j] == '.'){
				grid[i][j] = '!';
				found = true;
			}
		}
	}
	if(!found){
		for(int i = 0; i < 9; ++i){
			for(int j = 0; j < 9; ++j){
				if(grid[i][j] == '.'){
					grid[i][j] = '!';
				}
			}
		}
	}
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			cout << grid[i][j];
			if(j%3 == 2) cout << " ";
		}
		cout << "\n";
		if(i%3 == 2) cout << "\n";
	}
	return 0;
}