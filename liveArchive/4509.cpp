#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> point;

int inf = numeric_limits<int>::max();

int movs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct edge{
	point dest;
	int cost;
};

char mapa[30][30];
point holes[30][30];
int costsHoles[30][30];
int costs[30][30];
int processed[30][30];
bool inQueue[30][30];
edge candidates[5];

int w, h, V;

bool valid(int x, int y){
	return 0 <= x && x < w && 0 <= y && y < h && mapa[x][y] == '.';
}

void bellmanFord(){
	for(int i = 0; i < w; ++i){
		fill(costs[i], costs[i] + h, inf);
		fill(processed[i], processed[i] + h, 0);
		fill(inQueue[i], inQueue[i] + h, false);
	}
	queue<point> Q;
	costs[0][0] = 0;
	Q.push({0, 0});
	while(!Q.empty()){
		int x = Q.front().first, y = Q.front().second; Q.pop(); inQueue[x][y] = false;
		if(costs[x][y] == inf) continue;
		++processed[x][y];
		if(processed[x][y] == V){
			cout << "Never\n";
			return;
		}
		int valids = 0;
		point hole = holes[x][y];
		if(hole.first != -1){
			candidates[valids++] = {hole, costsHoles[x][y]};
		}else{
			if(!(x == w-1 && y == h-1))
			for(int i = 0; i < 4; ++i){
				int newX = x + movs[i][0];
				int newY = y + movs[i][1];
				if(valid(newX, newY)){
					candidates[valids++] = {{newX, newY}, 1};
				}
			}
		}
		for(int i = 0; i < valids; ++i){
			edge current = candidates[i];
			point dest = current.dest;
			int nuevo = costs[x][y] + current.cost;
			if(nuevo < costs[dest.first][dest.second]){
				if(!inQueue[dest.first][dest.second]){
					Q.push(dest);
					inQueue[dest.first][dest.second] = true;
				}
				costs[dest.first][dest.second] = nuevo;
			}
		}
	}
	if(costs[w - 1][h - 1] == inf) cout << "Impossible\n";
	else cout << costs[w - 1][h - 1] << "\n";
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	while(cin >> w >> h && !(w == 0 && h == 0)){
		V = w * h;
		for(int i = 0; i < w; ++i){
			fill(mapa[i], mapa[i] + h, '.');
			fill(holes[i], holes[i] + h, make_pair(-1, -1));
		}
		int g, e, x, y, x1, y1, x2, y2, t;
		cin >> g;
		for(int i = 0; i < g; ++i){
			cin >> x >> y;
			mapa[x][y] = '#';
			--V;
		}
		cin >> e;
		for(int i = 0; i < e; ++i){
			cin >> x1 >> y1 >> x2 >> y2 >> t;
			holes[x1][y1] = {x2, y2};
			costsHoles[x1][y1] = t;
		}
		if(w == 1 && h == 1){
			cout << "0\n";
			continue;
		}
		bellmanFord();
	}
	return 0;
}