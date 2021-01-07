#include <bits/stdc++.h>
using namespace std;

const vector<pair<int, int>> movs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

int process(vector<string> grid){
	bool change = true;
	int m = grid.size(), n = grid[0].size();
	auto valid = [&](int x, int y){
		return 0 <= x && x < m && 0 <= y && y < n;
	};
	while(change){
		change = false;
		auto nuevo = grid;
		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				int occupied = 0;
				for(auto mov : movs){
					int dx, dy;
					tie(dx, dy) = mov;
					if(valid(i+dx, j+dy)){
						occupied += (grid[i+dx][j+dy] == '#');
					}
				}
				if(grid[i][j] == 'L'){
					if(occupied == 0){
						nuevo[i][j] = '#';
						change = true;
					}
				}else if(grid[i][j] == '#'){
					if(occupied >= 4){
						nuevo[i][j] = 'L';
						change = true;
					}
				}
			}
		}
		grid = nuevo;
	}
	int ans = 0;
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			ans += (grid[i][j] == '#');
		}
	}
	return ans;
}

int main(){
	vector<string> grid;
	string linea;
	while(cin >> linea){
		grid.push_back(linea);
	}
	cout << process(grid) << "\n";
	return 0;
}