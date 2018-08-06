#include <bits/stdc++.h>
using namespace std;

int original[4][4];
int arr[4][4];

inline bool valid(int x, int y){
	return 0 <= x && x < 4 && 0 <= y && y < 4;
}

bool valid(){
	int b = 0, w = 0;
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < 4; ++j){
			if(arr[i][j] == 1) ++b;
			else ++w;
		}
	}
	return (b == 0 && w == 16) || (b == 16 && w == 0);
}

int movs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool flip(int x, int y){
	arr[x][y] *= -1;
	for(int l = 0; l < 4; ++l){
		int i = x + movs[l][0], j = y + movs[l][1];
		if(valid(i, j)) arr[i][j] *= -1;
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	char c;
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < 4; ++j){
			cin >> c;
			original[i][j] = (c == 'b' ? 1 : -1);
		}
	}
	int ans = 1 << 30;
	for(int mask = 0; mask < (1 << 16); ++mask){
		int m = 0;
		for(int i = 0; i < 4; ++i){
			for(int j = 0; j < 4; ++j){
				arr[i][j] = original[i][j];
			}
		}
		for(int p = 0; p < 16; ++p){
			if((mask >> p) & 1){
				flip(p / 4, p % 4);
				++m;
			}
		}
		if(valid()) ans = min(ans, m);
	}
	if(ans == 1<<30) cout << "Impossible\n";
	else cout << ans << "\n";
	return 0;
}