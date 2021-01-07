#include <bits/stdc++.h>
using namespace std;

int process(const vector<string> & grid, int right, int down){
	int ans = 0;
	int m = grid.size(), n = grid[0].size();
	int i = 0, j = 0;
	while(i < m){
		ans += (grid[i][j] == '#');
		i += down;
		j = (j + right) % n;
	}
	return ans;
}

int main(){
	vector<string> grid;
	string linea;
	while(cin >> linea){
		grid.push_back(linea);
	}
	cout << process(grid, 3, 1) << "\n";
	return 0;
}