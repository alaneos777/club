#include <bits/stdc++.h>
using namespace std;

struct point{
	int x, y;
	bool operator<(const point & p) const{
		if(y == p.y){
			return x > p.x;
		}else{
			return y < p.y;
		}
	}
};

struct region{
	point p;
	int count;
	char c;
	bool operator<(const region & r) const{
		if(count == r.count){
			return r.p < p;
		}else{
			return count < r.count;
		}
	}
};

int movs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int inf = 1 << 30;

char grid[10][15];
char tmp[10][15];
bool visited[10][15];
char column[10];

bool valid(const point & p, char c){
	return 0 <= p.x && p.x < 10 && 0 <= p.y && p.y < 15 && !visited[p.x][p.y] && grid[p.x][p.y] == c;
}

region bfs1(int i, int j){
	queue<point> Q;
	Q.push({i, j});
	visited[i][j] = true;
	char c = grid[i][j];
	int count = 1;
	point r = {i, j};
	while(!Q.empty()){
		point p = Q.front(); Q.pop();
		for(int k = 0; k < 4; ++k){
			point q = {p.x + movs[k][0], p.y + movs[k][1]};
			if(valid(q, c)){
				Q.push(q);
				visited[q.x][q.y] = true;
				r = min(r, q);
				++count;
			}
		}
	}
	return {r, count, c};
}

void bfs2(int i, int j){
	queue<point> Q;
	Q.push({i, j});
	visited[i][j] = true;
	char c = grid[i][j];
	while(!Q.empty()){
		point p = Q.front(); Q.pop();
		grid[p.x][p.y] = '.';
		for(int k = 0; k < 4; ++k){
			point q = {p.x + movs[k][0], p.y + movs[k][1]};
			if(valid(q, c)){
				Q.push(q);
				visited[q.x][q.y] = true;
			}
		}
	}
}

void compress1(){
	for(int j = 0; j < 15; ++j){
		int count = 0;
		for(int i = 0; i < 10; ++i){
			if(grid[i][j] != '.'){
				column[count++] = grid[i][j];
			}
		}
		for(int i = 0; i < 10 - count; ++i){
			grid[i][j] = '.';
		}
		for(int i = 10 - count; i < 10; ++i){
			grid[i][j] = column[i - (10 - count)];
		}
	}
}

void compress2(){
	int count = 0;
	memset(tmp, '.', sizeof(tmp));
	for(int j = 0; j < 15; ++j){
		bool empty = true;
		for(int i = 0; i < 10; ++i){
			empty &= (grid[i][j] == '.');
			column[i] = grid[i][j];
		}
		if(!empty){
			for(int i = 0; i < 10; ++i){
				tmp[i][count] = column[i];
			}
			++count;
		}
	}
	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 15; ++j){
			grid[i][j] = tmp[i][j];
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	for(int game = 1; game <= t; ++game){
		for(int i = 0; i < 10; ++i){
			for(int j = 0; j < 15; ++j){
				cin >> grid[i][j];
			}
		}
		if(game > 1) cout << "\n";
		cout << "Game " << game << ":\n\n";
		int score = 0;
		int remaining = 150;
		int move = 1;
		while(true){
			memset(visited, false, sizeof(visited));
			region maxima;
			bool first = true;
			for(int i = 0; i < 10; ++i){
				for(int j = 0; j < 15; ++j){
					if(grid[i][j] != '.' && !visited[i][j]){
						region actual = bfs1(i, j);
						if(actual.count >= 2){
							if(first){
								first = false;
								maxima = actual;
							}else{
								maxima = max(maxima, actual);
							}
						}
					}
				}
			}
			if(first) break;
			int points = (maxima.count - 2) * (maxima.count - 2);
			score += points;
			remaining -= maxima.count;
			memset(visited, false, sizeof(visited));
			bfs2(maxima.p.x, maxima.p.y);
			compress1();
			compress2();
			cout << "Move " << move++ << " at (" << 10-maxima.p.x << "," << maxima.p.y+1 << "): removed " << maxima.count << " balls of color " << maxima.c << ", got " << points << " points.\n";
		}
		if(remaining == 0) score += 1000;
		cout << "Final score: " << score << ", with " << remaining << " balls remaining.\n";
	}
	return 0;
}