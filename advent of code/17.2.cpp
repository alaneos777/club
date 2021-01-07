#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 15;
char grid[3*M][3*M][3*M][3*M];

int process(){
	bool change = true;
	int cnt = 0;
	while(change){
		cnt++;
		change = false;
		char nueva[3*M][3*M][3*M][3*M];
		memcpy(nueva, grid, sizeof(grid));
		for(int i = -M; i <= M; ++i){
			for(int j = -M; j <= M; ++j){
				for(int k = -M; k <= M; ++k){
					for(int l = -M; l <= M; ++l){
						int active = 0;
						//
						for(int x = -1; x <= 1; ++x){
							for(int y = -1; y <= 1; ++y){
								for(int z = -1; z <= 1; ++z){
									for(int w = -1; w <= 1; ++w){
										if(x == 0 && y == 0 && z == 0 && w == 0) continue;
										active += (grid[i+x+M+1][j+y+M+1][k+z+M+1][l+w+M+1] == '#');
									}
								}
							}
						}
						//
						if(grid[i+M+1][j+M+1][k+M+1][l+M+1] == '#'){
							if(!(active == 2 || active == 3)){
								nueva[i+M+1][j+M+1][k+M+1][l+M+1] = '.';
								change = true;
							}
						}else{
							if(active == 3){
								nueva[i+M+1][j+M+1][k+M+1][l+M+1] = '#';
								change = true;
							}
						}
					}
				}
			}
		}
		memcpy(grid, nueva, sizeof(grid));
		if(cnt == 6) break;
	}
	int ans = 0;
	for(int i = -M; i <= M; ++i){
		for(int j = -M; j <= M; ++j){
			for(int k = -M; k <= M; ++k){
				for(int l = -M; l <= M; ++l){
					ans += (grid[i+M+1][j+M+1][k+M+1][l+M+1] == '#');
				}
			}
		}
	}
	return ans;
}

int main(){
	string line;
	int i = 0;
	memset(grid, '.', sizeof(grid));
	while(getline(cin, line)){
		for(int j = 0; j < line.size(); ++j){
			grid[i+M+1][j+M+1][0+M+1][0+M+1] = line[j];
		}
		++i;
	}

	cout << process() << endl;

	return 0;
}