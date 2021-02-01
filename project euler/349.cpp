#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

bool grid[500][500];

int main(){
	int x = 100, y = 100;
	int dir = 0;
	int sum = 0;
	int M = 11000;
	lli N = 1e18;
	vector<int> a(M+1);
	for(int i = 1; i <= M; ++i){
		if(grid[x][y] == 0){
			dir = (dir + 3) & 3;
		}else{
			dir = (dir + 1) & 3;
		}
		if(grid[x][y] == 0) sum++;
		else sum--;
		grid[x][y] ^= 1;
		if(dir == 0) y++;
		else if(dir == 1) x--;
		else if(dir == 2) y--;
		else x++;
		a[i] = sum;
	}
	lli k = (N - M + 103) / 104;
	lli ans = 12*k + a[N - 104*k];
	cout << ans << "\n";
	return 0;
}