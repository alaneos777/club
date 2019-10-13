#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int h, w;
	cin >> h >> w;
	vector<vector<char>> grid(h, vector<char>(w));
	int cnt = 0, cx = 0, cy = 0;
	int leftMost = 1001, rightMost = -1;
	for(int i = 0; i < h; ++i){
		for(int j = 0; j < w; ++j){
			cin >> grid[i][j];
			if(grid[i][j] != '.'){
				cnt++;
				cy += i*2 + 1;
				cx += j*2 + 1;
			}
		}
	}
	cnt *= 2;
	for(int j = 0; j < w; ++j){
		if(grid[h-1][j] == '.') continue;
		leftMost = min(leftMost, j);
		rightMost = max(rightMost, j);
	}
	rightMost++;
	if(cnt*leftMost < cx && cx < cnt*rightMost){
		cout << "balanced\n";
	}else if(cx < cnt*leftMost){
		cout << "left\n";
	}else if(rightMost*cnt < cx){
		cout << "right\n";
	}
	//cout << leftMost << " " << rightMost << "\n" << (double)cx/cnt << " " << (double)cy/cnt << "\n";
	return 0;
}