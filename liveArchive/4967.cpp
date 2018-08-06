#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;

int movs[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

int n;

bool valid(int x, int y){
	return 0 <= x && x < n && 0 <= y && y < 3;
}

int ans(vector<vector<int>> & matrix){
	priority_queue<piii, vector<piii>, greater<piii>> Q;
	vector<vector<bool>> visited(n, vector<bool>(3, false));
	vector<vector<int>> info(n, vector<int>(3, 1 << 29));
	Q.push({{0, 1}, 0});
	info[0][1] = 0;
	while(!Q.empty()){
		pii dest = Q.top().first;
		int costo = Q.top().second;
		Q.pop();
		int x = dest.first, y = dest.second;
		if(x == n - 1 && y == 1) return costo;
		visited[x][y] = true;
		for(int i = 0; i < 4; ++i){
			int newX = x + movs[i][0], newY = y + movs[i][1];
			if(valid(newX, newY) && !visited[newX][newY]){
				int nuevo = info[x][y] + matrix[newX][newY];
				if(nuevo < info[newX][newY]){
					info[newX][newY] = nuevo;
					Q.push({{newX, newY}, nuevo});
				}
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int caso = 0;
	while(cin >> n && n){
		vector<vector<int>> matrix(n, vector<int>(3));
		for(int i = 0; i < n; ++i){
			cin >> matrix[i][0] >> matrix[i][1] >> matrix[i][2];
		}
		cout << ++caso << ". " << ans(matrix) + matrix[0][1] << "\n";
	}
	return 0;
}