#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> par;

int movs[2][2] = {{0, 1}, {1, 0}};

int n = 80;
int x0 = 0, y0 = 0, xf = n - 1, yf = n - 1;

int valid(int x, int y){
	return 0 <= x && x < n && 0 <= y && y < n;
}

int main(){
	ifstream in("p081_matrix.txt");
	vector<vector<int>> matrix(n, vector<int>(n));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			in >> matrix[i][j];
		}
	}

	set<pair<int, par>> info;
	vector<vector<bool>> visited(n, vector<bool>(n, false));
	vector<vector<int>> costs(n, vector<int>(n, 1 << 29));
	info.insert(make_pair(matrix[x0][y0], make_pair(x0, y0)));
	costs[x0][y0] = matrix[x0][y0];

	while(!info.empty()){
		auto actual = *info.begin();
		info.erase(info.begin());
		int x = actual.second.first, y = actual.second.second;
		if(visited[x][y]) continue;
		if(x == xf && y == yf) break;
		visited[x][y] = true;
		for(int i = 0; i < 2; i++){
			int xNew = x + movs[i][0], yNew = y + movs[i][1];
			if(valid(xNew, yNew) && !visited[xNew][yNew]){
				int sum = actual.first + matrix[xNew][yNew];
				if(sum < costs[xNew][yNew]){
					costs[xNew][yNew] = sum;
					info.insert(make_pair(sum, make_pair(xNew, yNew)));
				}
			}
		}
	}

	cout << costs[xf][yf] << "\n";
	return 0;
}