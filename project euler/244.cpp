#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using tup = tuple<int, int, int>;

const lli mod = 1e8 + 7;

int get(int board, int x, int y){
	return (board >> (4*x+y)) & 1;
}

int put(int board, int x, int y, int val){
	board &= ~(1 << (4*x+y));
	return board | (val << (4*x+y));
}

int change(int board, int x, int y, int nx, int ny){
	int val = get(board, nx, ny);
	board = put(board, x, y, val);
	board = put(board, nx, ny, 0);
	return board;
}

bool valid(int x, int y){
	return 0 <= x && x < 4 && 0 <= y && y < 4;
}

const pair<int, int> movs[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

queue<tup> q;
int dis[4][4][1<<16];
vector<tup> parents[4][4][1<<16];

int main(){
	for(int x = 0; x < 4; ++x){
		for(int y = 0; y < 4; ++y){
			for(int b = 0; b < (1<<16); ++b){
				dis[x][y][b] = 1e9;
			}
		}
	}

	int source_board = ((1<<2) + (1<<3)) * (1 + (1<<4) + (1<<8) + (1<<12));
	int source_x = 0, source_y = 0;

	int target_board = ((1<<1) + (1<<3) + (1<<4) + (1<<6)) * (1 + (1<<8));
	int target_x = 0, target_y = 0;

	//int target_board = ((1<<0) + (1<<1) + (1<<2) + (1<<3)) * ((1<<8) + (1<<12));
	//int target_x = 0, target_y = 0;

	//int target_board = (1<<2) + (1<<4) + (1<<8) + (1<<9) + (1<<10) + (1<<12) + (1<<13) + (1<<15);
	//int target_x = 3, target_y = 2;

	q.emplace(source_x, source_y, source_board);
	dis[source_x][source_y][source_board] = 0;
	parents[source_x][source_y][source_board] = {};

	while(!q.empty()){
		auto[x, y, board] = q.front(); q.pop();
		for(auto[dx, dy] : movs){
			int nx = x + dx, ny = y + dy;
			if(valid(nx, ny)){
				int nboard = change(board, x, y, nx, ny);
				if(dis[x][y][board] + 1 < dis[nx][ny][nboard]){
					dis[nx][ny][nboard] = dis[x][y][board] + 1;
					parents[nx][ny][nboard] = {{x, y, board}};
					q.emplace(nx, ny, nboard);
				}else if(dis[x][y][board] + 1 == dis[nx][ny][nboard]){
					parents[nx][ny][nboard].emplace_back(x, y, board);
				}
			}
		}
	}

	lli ans = 0;
	int cnt = 0;
	string path;
	function<void(int, int, int)> go = [&](int x, int y, int board){
		if(parents[x][y][board].size() == 0){
			reverse(path.begin(), path.end());
			lli checksum = 0;
			for(char c : path){
				checksum = (checksum*243 + c) % mod;
			}
			ans += checksum;
			cout << ++cnt << ": " << path << "\n";
			reverse(path.begin(), path.end());
		}else{
			for(auto[px, py, nboard] : parents[x][y][board]){
				char c = 'x';
				if(x == px && y < py) c = 'R';
				else if(x == px && y > py) c = 'L';
				else if(y == py && x < px) c = 'D';
				else if(y == py && x > px) c = 'U';
				path += c;
				go(px, py, nboard);
				path.pop_back();
			}
		}
	};

	go(target_x, target_y, target_board);

	cout << ans << "\n";

	return 0;
}